#pragma once

#include "Engine/Hackables/HackableObject.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class HackableData;
class KSequence;
class SmartAnimationSequenceNode;
class Sound;
class WorldSound;

class SquallyShip : public HackableObject
{
public:
	static SquallyShip* create(cocos2d::ValueMap& properties);

	static const std::string MapKey;

protected:
	SquallyShip(cocos2d::ValueMap& properties);
	virtual ~SquallyShip();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	cocos2d::Vec2 getButtonOffset() override;
	void registerHackables() override;

private:
	typedef HackableObject super;

	void runShipSequence();
	void onCrash();

	bool hasCrashed = false;
	float flightTime = 0.0f;

	SmartAnimationSequenceNode* lightningStrike = nullptr;
	cocos2d::Node* shipContainer = nullptr;
	cocos2d::Sprite* ship = nullptr;
	CollisionObject* shipCollision = nullptr;
	SmartAnimationSequenceNode* smokeAnimation = nullptr;
	SmartAnimationSequenceNode* shipFireAnimation = nullptr;
	SmartAnimationSequenceNode* fireAnimation = nullptr;
	SmartAnimationSequenceNode* thrustAnimation = nullptr;
	SmartAnimationSequenceNode* explodeAnimation = nullptr;
	SmartAnimationSequenceNode* fireRingAnimation = nullptr;
	SmartAnimationSequenceNode* groundFireAnimation = nullptr;
	SmartAnimationSequenceNode* groundFireSmallAnimation = nullptr;
	KSequence* skipSequence = nullptr;

	Sound* lightningSound = nullptr;
	Sound* thrusterSound = nullptr;
	Sound* enterAtmosphereSound = nullptr;
	Sound* crashSound = nullptr;
	WorldSound* fireSound = nullptr;
};
