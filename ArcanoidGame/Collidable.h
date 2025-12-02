#pragma once
#include <SFML/Graphics.hpp>
#include <memory>

namespace ArcanoidGame
{
	class Collidable
	{
	protected:
		virtual void OnHit() = 0;

	public:
		virtual bool CheckCollision(std::shared_ptr<Collidable> collidable) {
			if (GetCollision(collidable))
			{
				OnHit();
				collidable->OnHit();
				return true;
			}
			return false;
		};

		virtual bool GetCollision(std::shared_ptr<Collidable> collidable) const = 0;
	};
}