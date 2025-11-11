#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace SnakeGame
{
	class Ball : public GameObject
	{
	public:
		void Init();
		void Update(float timeDelta);

		void ReboundFromPlatform();

	private:
		sf::Vector2f direction;
	};
}


