#pragma once
#include "SFML/Graphics.hpp"
#include "GameObject.h"
#include "Collidable.h"
#include "IObserver.h"


namespace ArcanoidGame
{
	class Ball final : public GameObject, public Collidable, public IObservable
	{
	public:
		Ball(const sf::Vector2f& position); //Это будет замена инициализации
		~Ball() = default;

		void Update(float timeDelta) override;
		
		void ChangeDirectionX();
		void ChangeDirectionY();

		void SetSpeed(float speed);
		float GetSpeed() const;
		void SetColor(const sf::Color& color);

		bool GetCollision(std::shared_ptr<Collidable> collidable) const  override;
		void ChangeAngle(float x);
		///
		void SetSavedPosition(sf::Vector2f position) { sprite.setPosition(position); ChangeDirectionY(); };

		void restart() override;

		void Draw(sf::RenderWindow& window) override { GameObject::Draw(window); };

	private:
		void OnHit();
		sf::Vector2f direction;
		float lastAngle = 90.f;
		float multiplySpeed = 1.f;
		float speed;
	};
}


