#pragma once

#include "Engine/Maps/GameObject.h"

class CollisionObject;
class HackableData;

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
	static const std::string MapEventTorchLogicSwitchPrefix;
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

	/*
	bool isSolved();
	void computeIsOpen(bool isInstant);
	void checkComplete();
	*/

	Operation operation;
	std::string operationName;
	std::string puzzleTag;
};
