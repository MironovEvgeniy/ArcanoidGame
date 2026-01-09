#include "Game.h"
#include "Application.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "GameStatePlaying.h"
#include "PlayingMemento.h"
#include "FireBall.h"
#include "FragileBlock.h"
#include "BonusManager.h"
#include "randomizer.h"


namespace ArcanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));

		//Init factories
		factories.emplace(BlockType::Smooth, std::make_unique<SmoothBlockFactory>());
		factories.emplace(BlockType::Strong, std::make_unique<StrongBlockFactory>());
		factories.emplace(BlockType::Unbreackable, std::make_unique<UnbreackableBlockFactory>());

		// Init background
		background.setSize(sf::Vector2f(SETTINGS.SCREEN_WIDTH, SETTINGS.SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color::Black);

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		//Init platform and ball
		gameObjects.emplace_back(std::make_shared<Platform>(sf::Vector2f( SETTINGS.SCREEN_WIDTH / 2.0, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT / 2.f )));
		
		
		auto ball = std::make_shared<Ball>(sf::Vector2f(SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE - 200.f));
		ball->AddObserver(weak_from_this());
		gameObjects.emplace_back(ball);

		scoreSystem = std::make_shared<ScoreSystem>();
		createBlocks();
		saveSystem.Store(Save());
		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PauseGame();
			}
			else if (event.key.code == sf::Keyboard::S)
			{
				saveSystem.Store(Save());////CОХРАНЕНИЕ
			}
		}
	}

	void GameStatePlayingData::Update(float timeDelta)
	{	
		for (auto&& object : gameObjects)
		{
			object->Update(timeDelta);
		}

		for (auto&& block : blocks)
		{
			block->Update(timeDelta);
		}

		BonusManager::Update(timeDelta);
		UpdateBonuses(timeDelta);
		HandleBonusCollisions();

		std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);

		const bool isCollision = platform->CheckCollision(ball);
				
		bool inverseX = false;
		bool inverseY = false;
		
		bool isBlockBroken = false;

		for (int i = blocks.size() - 1; i >= 0; --i)
		{
			if (!(isBlockBroken) && blocks[i]->CheckCollision(ball))
			{
				isBlockBroken = true;
				const auto ballPos = ball->GetPosition();
				const auto blockRect = blocks[i]->GetRect();

				BallInverse(ballPos, blockRect, inverseX, inverseY);							
			}
			if (blocks[i]->IsBroken())
			{
				blocks.erase(blocks.begin() + i);
				return;
			}
		}
		
		if (inverseX)
		{
			ball->ChangeDirectionX();
		}

		if (inverseY)
		{
			ball->ChangeDirectionY();
		}		
	}

	void GameStatePlayingData::Draw(sf::RenderWindow& window)
	{
		// Draw background
		window.draw(background);

		// Draw game objects
		for (auto&& object : gameObjects)
		{
			object->Draw(window);
		}
		/*gameObjects[0]->Draw(window);
		BallVis->Draw(window);*/

		for (auto&& block : blocks)
		{
			block->Draw(window);
		}

		for (auto&& bonus : bonuses)
		{
			bonus->Draw(window);
		}

		scoreText.setString(std::to_string(scoreSystem->GetPlayerScore()));
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::LoadNextLevel()
	{
		if (currentLevel >= levelLoader.GetLevelCount() - 1) {
			Game& game = Application::Instance().GetGame();
			game.UpdateRecord(SETTINGS.PLAYER_NAME, scoreSystem->GetPlayerScore());
			game.setLastGameScore(scoreSystem->GetPlayerScore());
			game.WinGame();
		}
		else
		{
			std::shared_ptr <Platform> platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
			std::shared_ptr<Ball> ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
			platform->restart();
			ball->restart();

			blocks.clear();
			++currentLevel;
			createBlocks();
		}
	}

	void GameStatePlayingData::Notify(std::shared_ptr<IObservable> observable)
	{
		Game& game = Application::Instance().GetGame();

		if (auto block = std::dynamic_pointer_cast<Block>(observable); block) {
			--breackableBlocksCount;
			if (breackableBlocksCount == 0) {
				game.LoadNextLevel();
			}
			else
			{
				CreateBonus(block->GetPosition());
			}
		}
		else if (auto ball = std::dynamic_pointer_cast<Ball>(observable); ball)
		{
			if (ball->GetPosition().y > gameObjects.front()->GetRect().top) 
			{				
				auto memento = saveSystem.Get();
				if (memento && playerLifes > 0)
				{
					playerLifes -= 1;
					Restore(memento);
				}
				else
				{
					gameOverSound.play();
					game.UpdateRecord(SETTINGS.PLAYER_NAME, scoreSystem->GetPlayerScore());
					game.setLastGameScore(scoreSystem->GetPlayerScore());
					Application::Instance().GetGame().LooseGame();
				}
					
			}
		}
	}

	std::shared_ptr<IMemento> GameStatePlayingData::Save() const
	{
		auto memento = std::make_shared<PlayingMemento>();

		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);

		memento->ballPos = ball->GetPosition();
		memento->platformPos = platform->GetPosition();
		memento->score = scoreSystem->GetPlayerScore();

		for (const auto& block : blocks)
		{
			BlockSave blockSave;
			blockSave.pos = block->GetPosition();
			blockSave.blockType = block->GetBlockType();

			memento->AliveBlocks.push_back(blockSave);
		}

		return memento;
	}

	void GameStatePlayingData::Restore(std::shared_ptr<IMemento> memento)
	{
		auto playingMemento = std::dynamic_pointer_cast<PlayingMemento>(memento);

		if (!playingMemento) return;

		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);

		ball->SetSavedPosition(playingMemento->ballPos); //Пока реализована только позиция мяча
		scoreSystem->SetPlayerScoreFromSave(playingMemento->score);

		blocks.clear();
		breackableBlocksCount = 0;

		for (const auto& save : playingMemento->AliveBlocks)
		{
			auto block = factories.at(save.blockType)->createBlock(save.pos);

			block->AddObserver(weak_from_this());
			block->AddObserver(scoreSystem->weak_from_this());

			blocks.push_back(block);

			if (save.blockType != BlockType::Unbreackable)
				++breackableBlocksCount;
		}

	}

	void GameStatePlayingData::CreateBonus(const sf::Vector2f& position)
	{
		if (rand() % 100 < 80)
		{

			BonusType type = static_cast<BonusType>(rand() % 3);
			sf::Color color;

			switch (type)
			{
			case BonusType::FireBall:
				color = sf::Color::Red;
				break;
			case BonusType::FragileBlocks:
				color = sf::Color::Blue;
				break;
			case BonusType::IncreasePlatformSize:
				color = sf::Color::Green;
				break;
			default:
				color = sf::Color::White;
				break;
			}

			sf::Vector2f bonusPosition = position;
			bonusPosition.y += SETTINGS.BLOCK_HEIGHT;

			auto bonus = std::make_shared<Bonus>(bonusPosition, color, type);
			bonuses.push_back(bonus);
		}
	}

	void GameStatePlayingData::UpdateBonuses(float timeDelta)
	{
		for (auto& bonus : bonuses)
		{
			bonus->Update(timeDelta);
		}

		bonuses.erase(
			std::remove_if(bonuses.begin(), bonuses.end(),
				[](const std::shared_ptr<Bonus>& bonus) {
					return !bonus->IsActive();
				}),
			bonuses.end()
		);
	}

	void GameStatePlayingData::HandleBonusCollisions()
	{
		auto platform = std::dynamic_pointer_cast<Platform>(gameObjects[0]);
		auto ball = std::dynamic_pointer_cast<Ball>(gameObjects[1]);
		if (!platform)
		{
			return;
		}

		for (auto& bonus : bonuses)
		{
			if (bonus->CheckCollision(platform))
			{
				bonus->OnHit(); 
				switch (bonus->GetType())
				{
				case BonusType::FireBall: // Íîâûé áîíóñ

					BonusManager::ActivateFastBallBonus(5.0f);
					break;
				case BonusType::FragileBlocks:
					BonusManager::ActivateFragileBonus(10.0f);
					break;
				case BonusType::IncreasePlatformSize:
					BonusManager::ActivateSizeBonus(10.0f);
					break;
				default:
					break;
				}
			}
		}
	}

	void GameStatePlayingData::createBlocks()
	{
		for (const auto& pair : factories)
		{
			pair.second->clearCounter();
		}
		auto self = weak_from_this();

		auto level = levelLoader.GetLevel(currentLevel);

		for (auto pairPosBlockTYpe : level.m_blocks)
		{
			auto blockType = pairPosBlockTYpe.second;
			sf::Vector2i pos = pairPosBlockTYpe.first;

			sf::Vector2f position{
				(float)(SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + pos.x * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT))
				, (float)pos.y * SETTINGS.BLOCK_HEIGHT
			};

			//blocks.emplace_back(factories.at(blockType)->createBlock(position));
			blocks.emplace_back(factories.at(blockType)->createBlock(position));
			blocks.back()->AddObserver(self);

			blocks.back()->AddObserver(scoreSystem->weak_from_this());

		}

		for (const auto& pair : factories)
		{
			breackableBlocksCount += pair.second->GetCreatedBreackableBlocksCount();
		}
	}

	void GameStatePlayingData::BallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& inverseX, bool& inverseY)
	{
		//Низ блока
		if (ballPos.y > blockRect.top + blockRect.height)
		{
			inverseY = true;
		}
		//Левая часть
		if (ballPos.x < blockRect.left)
		{
			inverseX = true;
		}
		//Правая часть
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			inverseX = true;
		}
	}
}
