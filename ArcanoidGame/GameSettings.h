#pragma once
#include <string>

namespace ArcanoidGame
{
	class GameWorld
	{
	private:
		GameWorld() = default;

	public:
		static GameWorld& Instance()
		{
			static GameWorld gameWorld;
			return gameWorld;
		}

		// Resources path
		const std::string RESOURCES_PATH = "Resources/";
		const std::string TEXTURES_PATH = RESOURCES_PATH + "Textures/";
		const std::string FONTS_PATH = RESOURCES_PATH + "Fonts/";
		const std::string SOUNDS_PATH = RESOURCES_PATH + "Sounds/";
		const std::string LEVELS_CONFIG_PATH = RESOURCES_PATH + "levels.config";

		const float BREAK_DELAY = 0.1f;

		// Game settings constants
		const float ACCELERATION = 10.f;
		const unsigned int SCREEN_WIDTH = 800;
		const unsigned int SCREEN_HEIGHT = 600;
		const float TIME_PER_FRAME = 1.f / 60.f; // 60 fps

		const unsigned int BALL_SIZE = 20;
		const unsigned int BALL_SPEED = 400;
		const unsigned int BALL_BONUS_SPEED = 500;

		const unsigned int BLOCKS_COUNT_ROWS = 4;
		const unsigned int BLOCKS_COUNT_IN_ROW = 15;
		const unsigned int BLOCK_SHIFT = 10;
		const unsigned int BLOCK_WIDTH = (SCREEN_WIDTH - (BLOCKS_COUNT_IN_ROW + 1) * BLOCK_SHIFT) / BLOCKS_COUNT_IN_ROW;
		const unsigned int BLOCK_HEIGHT = 30;

		const unsigned int PLATFORM_WIDTH = 60;
		const unsigned int PLATFORM_HEIGHT = 20;
		const float PLATFORM_SPEED = 300.f;
		const unsigned int PLATFORM_BONUS_WIDTH = 180;
		const float PLATFORM_BONUS_SPEED = 400.f;

		const unsigned int BONUS_SIZE = 35;
		const unsigned int BONUS_FALL_SPEED = 150;

		const int MAX_RECORDS_TABLE_SIZE = 5;
		const char* PLAYER_NAME = "Player"; // We need to define this constant in some CPP

		const std::string GAME_NAME = "ArkanoidGame";

		const unsigned int MAX_APPLES = 80;

		const int SMOOTH_BLOCK_POINT = 5;
		const int STRONG_BLOCK_POINT = 10;

	};
}

#define SETTINGS GameWorld::Instance()