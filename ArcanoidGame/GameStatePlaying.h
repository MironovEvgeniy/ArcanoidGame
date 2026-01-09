#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"
#include "GameStateData.h"
#include "Block.h"
#include "StrongBlock.h"
#include "BlockFactory.h"
#include "LevelLoader.h"
#include "IObserver.h"
#include "IMemento.h"
#include "ScoreSystem.h"
#include "SaveSystem.h"
#include "Bonus.h"
#include "ICommand.h"

#include <unordered_map>



namespace ArcanoidGame
{
	class Game;

	class GameStatePlayingData : public GameStateData, public IObserver, public std::enable_shared_from_this<GameStatePlayingData>, public IMementoOriginator
	{
	public:
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;
		void LoadNextLevel();
		void Notify(std::shared_ptr<IObservable> observable) override;
		 
		virtual std::shared_ptr<IMemento> Save() const override;
		virtual void Restore(std::shared_ptr<IMemento> memento) override;

		//Bonuses
		void CreateBonus(const sf::Vector2f& position);
		void UpdateBonuses(float timeDelta);
		void HandleBonusCollisions();
		;

	private:
		void createBlocks();
		void BallInverse(const sf::Vector2f& ballPos, const sf::FloatRect& blockRect, bool& inverseX, bool& inverseY);

		// Resources
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		std::vector<std::shared_ptr<GameObject>> gameObjects;
		std::vector<std::shared_ptr<Block>> blocks;
		std::shared_ptr<ScoreSystem> scoreSystem;
		std::vector<std::shared_ptr<Bonus>> bonuses;
		SaveSystem saveSystem;

		int playerLifes = 3;

		//BlockCommand
		std::shared_ptr<ICommand> fragileBlockCommand;
		bool fragileBlocksActive = false;
		float fragileDuration = 0.0f;

		//FactoryData
		std::unordered_map<BlockType, std::unique_ptr<BlockFactory>> factories;
		int breackableBlocksCount = 0;

		//Levels
		LevelLoader levelLoader;
		int currentLevel = 2;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};
}
