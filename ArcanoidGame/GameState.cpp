#include "GameState.h"
#include "GameStatePlaying.h"
#include "GameStateGameOver.h"
#include "GameStatePauseMenu.h"
#include "GameStateMainMenu.h"
#include "GameStateRecords.h"
#include "GameStateWin.h"

#include <assert.h>


namespace ArcanoidGame
{
	GameState::GameState(GameStateType type, bool isExclusivelyVisible)
		: type(type)
		, isExclusivelyVisible(isExclusivelyVisible)
	{
		switch (type)
		{
		case GameStateType::MainMenu:
		{
			data = std::make_unique<GameStateMainMenuData>();
			break;
		}
		case GameStateType::Playing:
		{
			data = std::make_unique<GameStatePlayingData>();
			break;
		}
		case GameStateType::GameOver:
		{
			data = std::make_unique<GameStateGameOverData>();
			break;
		}
		case GameStateType::ExitDialog:
		{
			data = std::make_unique<GameStatePauseMenuData>();
			break;
		}
		case GameStateType::Records:
		{
			data = std::make_unique<GameStateRecordsData>();
			break;
		}
		case GameStateType::GameWin:
		{
			data = std::make_unique<GameStateWinData>();
			break;
		}
		default:
			assert(false); // We want to know if we forgot to implement new game state
			break;
		}
		if (data) { data->Init(); }
	}

	GameState::~GameState()
	{
		if (data) { data = nullptr; }
	}

	void GameState::Update(float timeDelta)
	{
		data->Update(timeDelta);
	}

	void GameState::Draw(sf::RenderWindow& window)
	{
		data->Draw(window);
	}

	void GameState::HandleWindowEvent(sf::Event& event)
	{
		data->HandleWindowEvent(event);
	}

	//void* GameState::CopyData(const GameState& state) const
	//{
	//	void* data = nullptr;
	//	switch (state.type)
	//	{
	//	case GameStateType::MainMenu:
	//	{
	//		data = new GameStateMainMenuData();
	//		*((GameStateMainMenuData*)data) = *(GameStateMainMenuData*)state.data;
	//		break;
	//	}
	//	case GameStateType::Playing:
	//	{
	//		data = new GameStatePlayingData();
	//		*((GameStatePlayingData*)data) = *(GameStatePlayingData*)state.data;
	//		break;
	//	}
	//	case GameStateType::GameOver:
	//	{
	//		data = new GameStateGameOverData();
	//		*((GameStateGameOverData*)data) = *(GameStateGameOverData*)state.data;
	//		break;
	//	}
	//	case GameStateType::ExitDialog:
	//	{
	//		data = new GameStatePauseMenuData();
	//		*((GameStatePauseMenuData*)data) = *(GameStatePauseMenuData*)state.data;
	//		break;
	//	}
	//	case GameStateType::Records:
	//	{
	//		data = new GameStateRecordsData();
	//		*((GameStateRecordsData*)data) = *(GameStateRecordsData*)state.data;
	//		break;
	//	}
	//	default:
	//		assert(false); // We want to know if we forgot to implement new game state
	//		break;
	//	}
	//	return data;
	//}
}