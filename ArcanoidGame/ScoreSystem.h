#pragma once
#include "IObserver.h"
#include "Block.h"
#include "StrongBlock.h"
#include "Game.h"


namespace ArcanoidGame
{
	class ScoreSystem : public IObserver, public std::enable_shared_from_this<ScoreSystem>
	{
	public:

		void Notify(std::shared_ptr<IObservable> observable) override;

		int GetPlayerScore() const { return playerScore; };
		void SetPlayerScoreFromSave (int scoreFromSave) { playerScore = scoreFromSave; };

	private:
		int playerScore = 0;
	};

}