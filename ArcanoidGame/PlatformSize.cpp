#include "PlatformSize.h"
#include "GameSettings.h"

namespace ArcanoidGame
{
	PlatformSize::PlatformSize(Platform& platform)
		: platform_(platform)
	{
	}

	void PlatformSize::Execute(Platform& platform)
	{
		auto newSize = SETTINGS.PLATFORM_BONUS_WIDTH;
		platform.SetSize(newSize);
	}

}