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

protected:
	LogicPuzzleController(cocos2d::ValueMap& properties);
	virtual ~LogicPuzzleController();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void computeIsOpen(bool isInstant);

	bool isSolved = false;

	std::map<Brazier::TorchColor, std::vector<Brazier*>> braziers;
	std::map<Brazier::TorchColor, LogicGate*> logicGates;

	Operation operation = Operation::None;
	std::string operationName;
	std::string puzzleTag;

	static const std::string SaveKeyIsSolved;
};
