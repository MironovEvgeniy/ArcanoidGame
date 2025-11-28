#pragma once
#include <SFML/Graphics.hpp>
#include "GameObject.h"

namespace ArcanoidGame
{
	class Ball;

	class Block : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;
		void Draw(sf::RenderWindow& window) override;

		bool CheckCollisionWithBall(const Ball& ball);

		//По идее лучше перенести в приватные и реализовывать задание позиций по другому
		sf::RectangleShape shape;

	private:
		
	};
}