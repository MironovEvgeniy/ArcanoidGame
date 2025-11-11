#pragma once
#include "SFML/Graphics.hpp"
#include "Menu.h"

namespace SnakeGame
{
	class Game;

	class GameStateMainMenuData
	{
	public:
		void Init();
		void HandleGameState(const sf::Event& event);
		void Update(float timeDelta);
		void Draw(sf::RenderWindow& window);

	private:
		sf::Font font;
		Menu menu;
	};
}
