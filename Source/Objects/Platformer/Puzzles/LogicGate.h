#pragma once

#include "Engine/Maps/GameObject.h"
#include "Objects/Platformer/Puzzles/LogicTorch.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;

class LogicGate : public GameObject
{
public:
	static LogicGate* create(cocos2d::ValueMap& properties);

	bool isSolved();

	static const std::string MapKey;

protected:
	LogicGate(cocos2d::ValueMap& properties);
	virtual ~LogicGate();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void computeIsOpen(bool isInstant);
	void checkComplete();
	void runGateAnim(bool isInstant);

	cocos2d::Sprite* gate;
	CollisionObject* gateCollision;

	LogicTorch::TorchColor torchColor;
	LogicTorch::Operation operation;
	std::string colorName;
	std::string operationName;
	std::string saveKey;
	bool answer;
	bool firstRun;
	bool isOpen;
	float delta;

	static const std::string PropertyGateColor;
	static const std::string PropertyDelta;
	static const std::string PropertyAnswer;
	static const std::string MapEventCheckComplete;
};
