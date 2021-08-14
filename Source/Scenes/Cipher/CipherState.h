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
class CipherLock;
class CipherPuzzleData;
class CipherState;
class ClickableNode;
class Connection;
class DestinationBlock;
class DisplayModeToggles;
class SourceBlock;

class CipherState : public SmartNode
{
public:
	enum class StateType
	{
		EmptyState,
		GameStart,
		LoadInitialState,
		Neutral,
		TransitionUnlocking,
		Unlocking,
		Testing,
		Wrong,
		Victory,
		GameEnd,
		Tutorial,
	};

	static CipherState* create();
	static void updateState(CipherState* gameState, StateType newState);
	void loadPuzzleData(CipherPuzzleData* puzzleData);
	void loadCipherAtIndex(int index);

	StateType stateType = StateType::EmptyState;
	StateType previousStateType = StateType::EmptyState;
	int gameDurationInSeconds = 0;
	std::function<void(bool)> updateStateCallback = nullptr;

	CipherPuzzleData* puzzleData = nullptr;
	std::vector<std::tuple<unsigned char, unsigned char>> inputOutputMap;
	std::vector<std::string> tokens;

	std::vector<SourceBlock*> inputBlocks;
	std::vector<DestinationBlock*> outputBlocks;
	std::vector<BlockBase*> userBlocks;
	std::vector<Connection*> userConnections;
	cocos2d::Node* inputContent = nullptr;
	cocos2d::Node* outputContent = nullptr;
	cocos2d::Node* blockContent = nullptr;
	cocos2d::Node* connectionContent = nullptr;
	CipherEvents::DisplayDataType displayDataType = CipherEvents::DisplayDataType::Ascii;
	
	cocos2d::LayerColor* gameAreaDebug = nullptr;

	std::string currentInput;
	std::string currentOutput;

	CipherLock* cipherLockPointer = nullptr;
	cocos2d::Node* unlockPointer = nullptr;
	DisplayModeToggles* displayModeTogglesPointer = nullptr;

protected:
	CipherState();
	virtual ~CipherState();

	void initializePositions() override;
	void initializeListeners() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;

	void clearInteraction();

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
