#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArcanoidGame
{
	class Ball : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;

		void ChangeDirectionX();
		void ChangeDirectionY();

	private:
		sf::Vector2f direction;
	};
}


