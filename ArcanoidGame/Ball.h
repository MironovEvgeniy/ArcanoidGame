#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include"Collidable.h"

namespace ArcanoidGame
{
	class Ball final : public GameObject, public Collidable
	{
	public:
		Ball(const sf::Vector2f& position); //Это будет замена инициализации
		~Ball() = default;

		void Update(float timeDelta) override;
		
		void ChangeDirectionX();
		void ChangeDirectionY();

		bool GetCollision(std::shared_ptr<Collidable> collidable) const  override;
		void ChangeAngle(float x);

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90.f;
	};
}


