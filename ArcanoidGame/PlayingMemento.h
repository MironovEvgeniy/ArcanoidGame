#pragma once
#include "IMemento.h"
#include <SFML/System/Vector2.hpp>
#include <vector>

namespace ArcanoidGame
{
	struct BlockSave
	{
		sf::Vector2f pos;
		BlockType blockType;
		bool isAlive;
	};

	class PlayingMemento final : public IMemento
	{
	public:
		sf::Vector2f ballPos;
		
		sf::Vector2f platformPos;
		std::vector<BlockSave> AliveBlocks;

		int score = 0;

	public:

		PlayingMemento() = default;

		PlayingMemento(const sf::Vector2f& inBallPos, const sf::Vector2f& inPlatformPos, std::vector<BlockSave> inAliveBlocks, int inScore)
			: ballPos(inBallPos)
			, platformPos(inPlatformPos)
			, AliveBlocks(std::move(inAliveBlocks))
			, score(inScore) { }

	};
}