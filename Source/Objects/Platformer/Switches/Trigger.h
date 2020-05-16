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
	static Trigger* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	Trigger(cocos2d::ValueMap& properties);
	virtual ~Trigger();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	CollisionObject* triggerCollision;
	bool wasActivated;
	bool multiTrip;
	bool saveState;

	static const std::string PropertySaveState;
	static const std::string PropertyMultiTrip;
};
