#pragma once

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

	static const std::string MapKey;

protected:
	LogicGate(cocos2d::ValueMap& properties);
	virtual ~LogicGate();

	void onEnter() override;
	void initializeListeners() override;
	void onToggle() override;
	void onEnable(bool isInit) override;
	void onDisable(bool isInit) override;

private:
	typedef ToggleableObject super;
	friend class BinderLogicGate;

	void runGateAnim(bool isInstant);

	cocos2d::Sprite* gate;
	CollisionObject* gateCollision;
	WorldSound* openSound;
	
	std::string colorName;
	std::string saveKey;
	bool answer;
	float delta;

	static const std::string PropertyGateColor;
	static const std::string PropertyDelta;
	static const std::string PropertyAnswer;
};
