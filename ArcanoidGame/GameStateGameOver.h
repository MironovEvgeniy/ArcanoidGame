#pragma once
#include "SFML/Graphics.hpp"
#include "GameStateData.h"


namespace ArcanoidGame
{
	class Game;

	class GameStateGameOverData : public GameStateData
	{
	public:
		
		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update( float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:
		
		sf::Font font;

		float timeSinceGameOver = 0.f;

		sf::RectangleShape background;
		sf::Text gameOverText;
		sf::Text hintText;
		sf::Text currentRecordText;
		std::vector<sf::Text> recordsTableTexts;
	};
}
