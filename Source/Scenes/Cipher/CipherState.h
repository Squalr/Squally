#pragma once
#include <chrono>
#include <vector>

#include "Engine/SmartNode.h"

class CipherPuzzleData;

class CipherState : public SmartNode
{
public:
	enum class StateType
	{
		EmptyState,
		GameStart,
		LoadInitialState,
		Neutral,
		Running,
		Wrong,
		Victory,
		GameEnd,
	};

	static CipherState* create();
	static void updateState(CipherState* gameState, StateType newState);
	void loadPuzzleData(CipherPuzzleData* puzzleData);

	StateType stateType;
	StateType previousStateType;
	int gameDurationInSeconds;
	std::function<void(bool)> updateStateCallback;

	CipherPuzzleData* puzzleData;
	std::vector<std::tuple<std::string, std::string>> inputOutputMap;

	// Tutorial node pointers
	cocos2d::Node* inputsOutputsPanelPointer;

	static const std::string RequestStateUpdateEvent;
	static const std::string BeforeStateUpdateEvent;
	static const std::string OnStateUpdateEvent;
private:
	CipherState();
	~CipherState();

	void initializePositions() override;
	void clearInteraction();

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
