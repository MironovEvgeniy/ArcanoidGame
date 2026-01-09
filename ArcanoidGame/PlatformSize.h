#pragma once
#include "ICommand.h"
#include "Platform.h"

namespace ArcanoidGame
{
	class PlatformSize : public ICommand
	{
	public:
		PlatformSize(Platform& platform);
		void Execute(Block& block) override {};
		void Execute(Ball& ball) override {};
		void Execute(Platform& platform) override;

	private:
		Platform& platform_;

	};

}
