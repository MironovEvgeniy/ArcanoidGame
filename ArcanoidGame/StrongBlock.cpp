#include "StrongBlock.h"
#include "Sprite.h"
#include"GameSettings.h"

namespace ArcanoidGame
{
	ArcanoidGame::StrongBlock::StrongBlock(const sf::Vector2f& position, sf::Color color)
		: SmoothDestroyableBlock(position, color)
	{
		hitCount = 2;
	}

	void StrongBlock::OnHit()
	{
		--hitCount;
		sprite.setColor(sf::Color::Red);

		if (hitCount == 0)
		{
			hitCount = 1;
			StartTimer(SETTINGS.BREAK_DELAY);
		}
	}

}
