#pragma once

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/Interactables/Puzzles/Brazier.h"

class Brazier;
class CollisionObject;
class HackableData;
class LogicGate;

class LogicPuzzleController : public GameObject
{
public:
	static LogicPuzzleController* create(cocos2d::ValueMap& properties);

	enum class Operation
	{
		None,
		And,
		Or,
		Xor
	};

	static Operation StrToOperation(std::string operationName);

	static const std::string MapKey;
	static const std::string PropertyOperation;
	
	static const std::string MapEventTorchLogicSwitchSavePrefix;
	static const std::string MapEventTorchLogicSwitch;
	static const std::string MapEventSolveTorches;
	static const std::string MapEventCheckComplete;
	static const std::string SaveKeyIsSolved;

protected:
	LogicPuzzleController(cocos2d::ValueMap& properties);
	virtual ~LogicPuzzleController();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void computeIsOpen(bool isInstant);
	void runGateAnims(bool isInstant);
	/*
	bool isSolved();
	void checkComplete();
	*/

	std::map<Brazier::TorchColor, std::vector<Brazier*>> braziers;
	std::map<Brazier::TorchColor, LogicGate*> logicGates;

	Operation operation;
	std::string operationName;
	std::string puzzleTag;
};
