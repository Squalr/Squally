#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;

class Trigger : public HackableObject
{
public:
	static Trigger* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeyTrigger;

protected:
	Trigger(cocos2d::ValueMap& initProperties);
	virtual ~Trigger();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	std::string triggerEventName;
	CollisionObject* triggerCollision;
	bool wasActivated;
};
