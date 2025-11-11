#include <SFML/Graphics.hpp>
#include "Game.h"

namespace SnakeGame
{
	class Application
	{
	public:
		Application(const Application& app) = delete; //удаляем конструктор копирование
		Application& operator= (const Application&) = delete; //удаляем оператор присваивания

		static Application& Instance();

		void Run();

		Game& GetGame() { return game; }

	private:
		Application();
		~Application();

	private:
		Game game;
		sf::RenderWindow window;
	};



}