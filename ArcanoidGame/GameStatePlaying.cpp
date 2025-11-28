#include "GameStatePlaying.h"
#include "Game.h"
#include "Application.h"
#include "Text.h"
#include <assert.h>
#include <sstream>

namespace ArcanoidGame
{
	void GameStatePlayingData::Init()
	{	
		// Init game resources (terminate if error)
		assert(font.loadFromFile(FONTS_PATH + "Roboto-Regular.ttf"));
		assert(gameOverSoundBuffer.loadFromFile(SOUNDS_PATH + "Death.wav"));

		// Init background
		background.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
		background.setPosition(0.f, 0.f);
		background.setFillColor(sf::Color(0, 200, 0));

		scoreText.setFont(font);
		scoreText.setCharacterSize(24);
		scoreText.setFillColor(sf::Color::Yellow);

		inputHintText.setFont(font);
		inputHintText.setCharacterSize(24);
		inputHintText.setFillColor(sf::Color::White);
		inputHintText.setString("Use arrow keys to move, ESC to pause");
		inputHintText.setOrigin(GetTextOrigin(inputHintText, { 1.f, 0.f }));

		//Init platform and ball
		
		gameObjects.clear();
		gameObjects.push_back(std::make_shared<Platform>());
		gameObjects.push_back(std::make_shared<Ball>());
		
		createBlocks();

		for (auto&& object : gameObjects)
		{
			object->Init();
		}

		for (auto&& block : blocks)
		{
			block->Init();
		}

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

		Platform* platform = (Platform*)gameObjects[0].get();
		Ball* ball = (Ball*)gameObjects[1].get();

		const bool isCollision = platform->CheckCollisionWithBall(*ball);
		if (isCollision) {
			ball->ChangeDirectionY();
		}
		
		//////////
		
			/*const bool isCollisionWithBlock = block->CheckCollisionWithBall(*ball);
			if (isCollisionWithBlock)
			{
				ball->ReboundFromPlatform();
				gameObjects.erase(gameObjects.begin() + 2);
			}
		*/
		bool inverseX = false;
		bool inverseY = false;

		for (int i = blocks.size() - 1; i >= 0; --i)
		{
			if (blocks[i]->CheckCollisionWithBall(*ball))
			{
				const auto ballPos = ball->GetPosition();
				const auto blockRect = blocks[i]->GetRect();

				BallInverse(ballPos, blockRect, inverseX, inverseY);

				blocks.erase(blocks.begin() + i);			
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
		for (; row < BLOCKS_COUNT_ROWS; ++row)
		{
			for (int col = 0; col < BLOCKS_COUNT_IN_ROW; ++col)
			{
				auto block = std::make_shared<Block>();
				block->shape.setPosition(sf::Vector2f({ BLOCK_SHIFT + BLOCK_WIDTH / 2.f + col * (BLOCK_WIDTH + BLOCK_SHIFT), 100.f + row * (BLOCK_HEIGHT + BLOCK_SHIFT) }));
				blocks.emplace_back(block);
			}
		}

	}

	void GameStatePlayingData::BallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& inverseX, bool& inverseY)
	{
		//Низ блока
		if (ballPos.y > blockRect.top + blockRect.height)
		{
			inverseY = true;
			return;
		}
		//Левая часть
		if (ballPos.x < blockRect.left)
		{
			inverseX = true;
			return;
		}
		//Правая часть
		if (ballPos.x > blockRect.left + blockRect.width)
		{
			inverseX = true;
			return;
		}
	}
}
