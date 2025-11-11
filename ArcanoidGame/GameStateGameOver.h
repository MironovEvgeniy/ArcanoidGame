#pragma once
#include "SFML/Graphics.hpp"

namespace SnakeGame
{
	class Game;

	class GameStateGameOverData
	{
	public:
		
		void Init();
		void HandleGameState(const sf::Event& event);
		void Update( float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		
		sf::Font font;

		float timeSinceGameOver = 0.f;

		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		std::vector<sf::Text> recordsTableTexts;
	};
}
