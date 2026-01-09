#include "BlockFactory.h"
#include "Block.h"
#include "StrongBlock.h"

namespace ArcanoidGame
{
	int BlockFactory::GetCreatedBreackableBlocksCount() {

		return createdBreackableBlocksCount;
	}

	void BlockFactory::clearCounter()
	{
		createdBreackableBlocksCount = 0;
	}

	std::shared_ptr<Block> SmoothBlockFactory::createBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<SmoothDestroyableBlock>(position);
	}

	std::shared_ptr<Block> UnbreackableBlockFactory::createBlock(const sf::Vector2f& position)
	{
		return std::make_shared<UnbreakableBlock>(position);
	}

	std::shared_ptr<Block> StrongBlockFactory::createBlock(const sf::Vector2f& position)
	{
		++createdBreackableBlocksCount;
		return std::make_shared<StrongBlock>(position);
	}



}