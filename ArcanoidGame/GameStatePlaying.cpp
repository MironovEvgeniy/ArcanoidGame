#include "Game.h"
#include "Application.h"
#include "Text.h"
#include <assert.h>
#include <sstream>
#include "GameStatePlaying.h"

namespace ArcanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(SETTINGS.FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SETTINGS.SOUNDS_PATH + "Death.wav"));

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
		gameObjects.emplace_back(std::make_shared<Ball>(sf::Vector2f( SETTINGS.SCREEN_WIDTH / 2.f, SETTINGS.SCREEN_HEIGHT - SETTINGS.PLATFORM_HEIGHT - SETTINGS.BALL_SIZE - 200.f )));
		createBlocks();

		// Init sounds
		gameOverSound.setBuffer(gameOverSoundBuffer);
	}

	void GameStatePlayingData::HandleWindowEvent(const sf::Event& event)
	{

		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
				Application::Instance().GetGame().PushState(GameStateType::ExitDialog, false);
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
		
		const bool isGameFinished = !isCollision && ball->GetPosition().y > platform->GetRect().top;
		const bool isGameWin = blocks.size() == 0;

		if (isGameWin)
		{
			Game& game = Application::Instance().GetGame();
			game.PushState(GameStateType::GameWin, false);
		}

		if (isGameFinished)
		{
			gameOverSound.play();

			Game& game = Application::Instance().GetGame();

			// Find player in records table and update his score
			//game.UpdateRecord(PLAYER_NAME, numEatenApples);
			game.PushState(GameStateType::GameOver, false);
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

		for (auto&& block : blocks)
		{
			block->Draw(window);
		}
		
		scoreText.setOrigin(GetTextOrigin(scoreText, { 0.f, 0.f }));
		scoreText.setPosition(10.f, 10.f);
		window.draw(scoreText);

		sf::Vector2f viewSize = window.getView().getSize();
		inputHintText.setPosition(viewSize.x - 10.f, 10.f);
		window.draw(inputHintText);
	}

	void GameStatePlayingData::createBlocks()
	{
		int row = 0;
		for (; row < SETTINGS.BLOCKS_COUNT_ROWS - 1; ++row)
		{
			for (int col = 0; col < SETTINGS.BLOCKS_COUNT_IN_ROW; ++col)
			{
				blocks.emplace_back(std::make_shared<SmoothDestroyableBlock>(sf::Vector2f({ SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + col * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT), 100.f + row * (SETTINGS.BLOCK_HEIGHT + SETTINGS.BLOCK_SHIFT) })));
			}
		}

		/*for (int col = 0; col < 3; ++col) 
		{
			blocks.emplace_back(std::make_shared<UnbreakableBlock>(sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * (BLOCK_HEIGHT + BLOCK_SHIFT) })));
		}*/

		for (int col = 0; col < SETTINGS.BLOCKS_COUNT_IN_ROW; ++col)
		{
			blocks.emplace_back(std::make_shared<StrongBlock>(sf::Vector2f({ SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + col * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT), 100.f + row * (SETTINGS.BLOCK_HEIGHT + SETTINGS.BLOCK_SHIFT) })));
		}

		blocks.emplace_back(std::make_shared<UnbreakableBlock>(sf::Vector2f({ SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + 0 * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT), 100.f + (row + 1) * (SETTINGS.BLOCK_HEIGHT + SETTINGS.BLOCK_SHIFT) })));
		blocks.emplace_back(std::make_shared<UnbreakableBlock>(sf::Vector2f({ SETTINGS.BLOCK_SHIFT + SETTINGS.BLOCK_WIDTH / 2.f + (SETTINGS.BLOCKS_COUNT_IN_ROW - 1) * (SETTINGS.BLOCK_WIDTH + SETTINGS.BLOCK_SHIFT), 100.f + (row + 1) * (SETTINGS.BLOCK_HEIGHT + SETTINGS.BLOCK_SHIFT) })));
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
