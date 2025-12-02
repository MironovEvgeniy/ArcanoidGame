#pragma once
#include "Ball.h"

#include "GameObject.h"
#include "Collidable.h"
#include "IDelayedAction.h"

namespace ArcanoidGame
{
	class Block : public GameObject, public Collidable
	{
	public:
		
		Block(const sf::Vector2f& position, const sf::Color& color = sf::Color::Green);
		virtual ~Block();

		bool GetCollision(std::shared_ptr<Collidable> collidable) const  override;

		void Update(float timeDelta) override;

		bool IsBroken();

	protected:
		void OnHit();
		int hitCount = 1;
	};

	class SmoothDestroyableBlock : public Block, public IDelayedAction
	{
	protected:
		void OnHit() override;
		sf::Color color;

	public:
		SmoothDestroyableBlock(const sf::Vector2f& position, sf::Color color = sf::Color::Green);
		~SmoothDestroyableBlock() = default;

		void Update(float timeDelta) override;
		bool GetCollision(std::shared_ptr<Collidable> collidable) const override;
		void FinalAction() override;
		void EachTickAction(float timeDelta) override;
	};

	class UnbreakableBlock : public Block
	{
	public:
		UnbreakableBlock(const sf::Vector2f& position);
		void OnHit() override;
		void Update(float timeDelta) override {
			int i = 0;
			++i;
		}
	};
}