#include <SFML/Graphics.hpp>
#include "Menu.h"
#include "GameStateData.h"

namespace ArcanoidGame
{
	class Game;

	class GameStateWinData : public GameStateData
	{
	public:

		void Init() override;
		void HandleWindowEvent(const sf::Event& event) override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

	private:

		sf::Font font;

		float timeSinceGameWin = 0.f;

		sf::RectangleShape background;
		sf::Text gameWinText;
		sf::Text hintText;

		Menu menu;
	};
}
