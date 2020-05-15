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

	static const std::string MapKey;

protected:
	LogicGate(cocos2d::ValueMap& properties);
	virtual ~LogicGate();

	void onEnter() override;
	void initializeListeners() override;

private:
	typedef GameObject super;

	void runGateAnim();

	cocos2d::Sprite* gate;
	CollisionObject* gateCollision;

	LogicTorch::TorchColor torchColor;
	LogicTorch::Operation operation;
	std::string saveKey;
	cocos2d::Vec2 spawnPosition;
	bool isOpen;
	float delta;

	static const std::string PropertyGateColor;
	static const std::string PropertyDelta;
	static const std::string PropertySaveKey;
};
