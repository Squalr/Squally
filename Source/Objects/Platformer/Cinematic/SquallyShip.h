#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class SmartAnimationSequenceNode;
class Sound;

class SquallyShip : public HackableObject
{
public:
	static SquallyShip* create(cocos2d::ValueMap& initProperties);

	static const std::string MapKeySquallyShip;

protected:
	SquallyShip(cocos2d::ValueMap& initProperties);
	virtual ~SquallyShip();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	bool hasCrashed;
	float flightTime;

	cocos2d::Node* shipContainer;
	cocos2d::Sprite* ship;
	CollisionObject* shipCollision;
	SmartAnimationSequenceNode* smokeAnimation;
	SmartAnimationSequenceNode* fireAnimation;
	SmartAnimationSequenceNode* thrustAnimation;
	SmartAnimationSequenceNode* explodeAnimation;
	SmartAnimationSequenceNode* fireRingAnimation;
	SmartAnimationSequenceNode* groundFireAnimation;
	SmartAnimationSequenceNode* groundFireSmallAnimation;

	Sound* thrusterSound;
	Sound* enterAtmosphereSound;
	Sound* crashSound;
	Sound* fireSound;

	static const float FlightTimeUntilRedFlame;
};
