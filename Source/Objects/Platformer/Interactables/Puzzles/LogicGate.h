#pragma once

#include "Objects/Platformer/Interactables/Puzzles/Brazier.h"
#include "Objects/Platformer/Interactables/ToggleableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class WorldSound;

class LogicGate : public ToggleableObject
{
public:
	static LogicGate* create(cocos2d::ValueMap& properties);

	Brazier::TorchColor getTorchColor();
	bool getAnswer() const { return this->answer; }

	static const std::string MapKey;

protected:
	LogicGate(cocos2d::ValueMap& properties);
	virtual ~LogicGate();

	void onEnter() override;
	void initializeListeners() override;
	void onToggle(bool isInstant = true) override;
	void onEnable(bool isInit, bool isInstant = true) override;
	void onDisable(bool isInit, bool isInstant = true) override;

private:
	typedef ToggleableObject super;
	friend class BinderLogicGate;

	void runGateAnim(bool isInstant);

	cocos2d::Sprite* gate = nullptr;
	CollisionObject* gateCollision = nullptr;
	WorldSound* openSound = nullptr;
	
	std::string torchColorName;
	Brazier::TorchColor torchColor = Brazier::TorchColor::Red;
	std::string saveKey;
	bool answer = false;
	float delta = 0.0f;

	static const std::string PropertyGateColor;
	static const std::string PropertyDelta;
	static const std::string PropertyAnswer;
};
