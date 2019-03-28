#pragma once
#include <chrono>
#include <vector>

#include "Engine/SmartNode.h"
#include "Events/CipherEvents.h"

namespace cocos2d
{
	class LayerColor;
}

class BlockBase;
class CipherPuzzleData;
class CipherState;
class ClickableNode;
class Connection;
class DestinationBlock;
class SourceBlock;

class CipherState : public SmartNode
{
public:
	enum class StateType
	{
		EmptyState,
		GameStart,
		LoadInitialState,
		TransitionNeutral,
		Neutral,
		TransitionUnlocking,
		Unlocking,
		Testing,
		Wrong,
		Victory,
		GameEnd,
	};

	static CipherState* create();
	static void updateState(CipherState* gameState, StateType newState);
	void loadPuzzleData(CipherPuzzleData* puzzleData);
	void loadCipherAtIndex(int index);

	StateType stateType;
	StateType previousStateType;
	int gameDurationInSeconds;
	std::function<void(bool)> updateStateCallback;

	CipherPuzzleData* puzzleData;
	std::vector<std::tuple<std::string, std::string>> inputOutputMap;

	std::vector<SourceBlock*> inputBlocks;
	std::vector<DestinationBlock*> outputBlocks;
	std::vector<BlockBase*> userBlocks;
	std::vector<Connection*> userConnections;
	cocos2d::Node* inputContent;
	cocos2d::Node* outputContent;
	cocos2d::Node* blockContent;
	cocos2d::Node* connectionContent;
	CipherEvents::DisplayDataType displayDataType;
	
	cocos2d::LayerColor* gameAreaDebug;

	std::string currentInput;
	std::string currentOutput;

	// Tutorial node pointers
	cocos2d::Node* lockPointer;
	cocos2d::Node* toolBoxPointer;

	static const std::string RequestStateUpdateEvent;
	static const std::string BeforeStateUpdateEvent;
	static const std::string OnStateUpdateEvent;

protected:
	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable() override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;
	CipherState();
	~CipherState();

	void clearInteraction();

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
