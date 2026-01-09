#pragma once
#include <SFML/Graphics.hpp>

#include "Snake.h"
#include "GameState.h"
#include "GameSettings.h"
#include <unordered_map>

namespace ArcanoidGame
{
	enum class GameOptions: std::uint8_t
	{
		InfiniteApples = 1 << 0,
		WithAcceleration = 1 << 1,

		Default = InfiniteApples | WithAcceleration,
		Empty = 0
	};

	enum class GameStateChangeType
	{
		None,
		Push,
		Pop,
		Switch
	};

	class Game
	{
	public:
		void StartGame();
		void PauseGame();
		void WinGame();
		void LooseGame();
		void UpdateGame(float timeDelta, sf::RenderWindow& window);
		void ExitGame();
		void QuitGame();
		void ShowRecords();
		void LoadNextLevel();

		using RecordsTable = std::unordered_map<std::string, int>;

		Game();
		~Game();

		bool IsEnableOptions(GameOptions option) const;
		void SetOption(GameOptions option, bool value);
		const RecordsTable& GetRecordsTable() const { return recordsTable; }
		int GetRecordByPlayerId(const std::string& playerId) const;
		void UpdateRecord(const std::string& playerId, int score);

		// Remove current game state from the stack
		void PopState();
		void setLastGameScore(int lastPlayerGameScore);
		int GetLastGameScore() const { return lastGameScore; };

	private:
		std::vector<GameState> stateStack;
		GameStateChangeType stateChangeType = GameStateChangeType::None;
		GameStateType pendingGameStateType = GameStateType::None;
		bool pendingGameStateIsExclusivelyVisible = false;

		GameOptions options = GameOptions::Default;
		RecordsTable recordsTable;

		int lastGameScore = 0;

		// Add new game state on top of the stack
		void PushState(GameStateType stateType, bool isExclusivelyVisible);

		void Shutdown();
		
		void HandleWindowEvents(sf::RenderWindow& window);

		bool Update(float timeDelta); // Return false if game should be closed
		void Draw(sf::RenderWindow& window);

		// Remove all game states from the stack and add new one
		void SwitchStateTo(GameStateType newState);
	};
}
