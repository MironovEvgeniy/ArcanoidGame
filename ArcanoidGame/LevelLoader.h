#pragma once

#include "Block.h"
#include "StrongBlock.h"

#include <vector>
#include <string>
#include <memory>
#include "BlockType.h"
#include <map>

namespace ArcanoidGame {
	/*enum class BlockType
	{
		Smooth,
		Strong,
		Unbreackable
	};*/

	struct Level {
		std::vector<std::pair<sf::Vector2i, BlockType>> m_blocks;
	};

	class LevelLoader final
	{
	public:
		LevelLoader() { LoadLevelsFromFile(); };
		Level& GetLevel(int i);
		~LevelLoader() = default;
		int GetLevelCount();
	private:
		void LoadLevelsFromFile();

		static BlockType CharToBlockType(char symbol);
		std::vector<Level> levels;
	};

}
