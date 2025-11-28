#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"

namespace ArcanoidGame
{
	class Ball;

	class Platform : public GameObject
	{
	public:
		void Init() override;
		void Update(float timeDelta) override;

		bool CheckCollisionWithBall(const Ball& ball);

	private:
		void Move(float speed);
	};
}