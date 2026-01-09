#include "ScoreSystem.h"
#include "Application.h"


namespace ArcanoidGame
{
	void ScoreSystem::Notify(std::shared_ptr<IObservable> observable)
	{
		if (auto block = std::dynamic_pointer_cast<Block>(observable); block)
		{
			Game& game = Application::Instance().GetGame();
			playerScore = playerScore + block->GetBlockPoint();
		}
	}
}

