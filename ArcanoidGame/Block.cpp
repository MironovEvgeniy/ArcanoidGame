#include "Block.h"
#include "Sprite.h"

#include "GameSettings.h"
#include <assert.h>


namespace
{
	const std::string TEXTURE_ID = "platform";
}

namespace ArcanoidGame
{
	Block::Block(const sf::Vector2f& position, const sf::Color& color)
		: GameObject(SETTINGS.TEXTURES_PATH + TEXTURE_ID + ".png", position, SETTINGS.BLOCK_WIDTH, SETTINGS.BLOCK_HEIGHT)
	{
		sprite.setColor(color);
	}

	Block::~Block()
	{
	}

	bool Block::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);

		sf::Rect rect = gameObject->GetRect();
		rect.width *= 1.1;
		return GetRect().intersects(gameObject->GetRect());
	}

	void Block::OnHit()
	{
		hitCount = 0;
		Emit();
	}

	void Block::Update(float timeDelta)
	{

	}

	bool Block::IsBroken()
	{
		return hitCount <= 0;
	}

	void SmoothDestroyableBlock::OnHit()
	{
		StartTimer(SETTINGS.BREAK_DELAY);
	}

	SmoothDestroyableBlock::SmoothDestroyableBlock(const sf::Vector2f& position, sf::Color color)
		: Block(position, color)
		, color(color)
	{
		BlockPoints = SETTINGS.SMOOTH_BLOCK_POINT;
		m_type = BlockType::Smooth;
	}

	void SmoothDestroyableBlock::Update(float timeDelta)
	{
		UpdateTimer(timeDelta);
	}

	bool SmoothDestroyableBlock::GetCollision(std::shared_ptr<Collidable> collidable) const
	{
		if (isTimerStarted_)
		{
			return false;
		}
		auto gameObject = std::dynamic_pointer_cast<GameObject>(collidable);
		assert(gameObject);

		sf::Rect rect = gameObject->GetRect();
		return GetRect().intersects(rect);
	}

	void SmoothDestroyableBlock::FinalAction()
	{
		--hitCount;
		Emit();
	}

	void SmoothDestroyableBlock::EachTickAction(float timeDelta)
	{
		color.a = 255 * currentTime_ / destroyTime_;
		sprite.setColor(color);
	}

	UnbreakableBlock::UnbreakableBlock(const sf::Vector2f& position)
		: Block(position, sf::Color::Color(105, 105, 105))
	{
		m_type = BlockType::Unbreackable;
	}

	void UnbreakableBlock::OnHit()
	{
	}

}