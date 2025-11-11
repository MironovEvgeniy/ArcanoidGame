#pragma once
#include "SFML/Graphics.hpp"
#include "SFML/Audio.hpp"
#include "Platform.h"
#include "Ball.h"


namespace SnakeGame
{
	class Game;

	class GameStatePlayingData
	{
	public:
		void Init();
		void HandleGameState(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		// Resources
		sf::Font font;
		sf::SoundBuffer eatAppleSoundBuffer;
		sf::SoundBuffer gameOverSoundBuffer;

		// Game data
		Platform platform;
		Ball ball;

		// UI data
		sf::Text scoreText;
		sf::Text inputHintText;
		sf::RectangleShape background;

		// Sounds
		sf::Sound eatAppleSound;
		sf::Sound gameOverSound;
	};
}
