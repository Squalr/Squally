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

class SquallyShip : public HackableObject
{
public:
	static SquallyShip* create(cocos2d::ValueMap& properties);

	static const std::string MapKeySquallyShip;

protected:
	SquallyShip(cocos2d::ValueMap& properties);
	~SquallyShip();

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

	bool hasCrashed;
	float flightTime;

	SmartAnimationSequenceNode* lightningStrike;
	cocos2d::Node* shipContainer;
	cocos2d::Sprite* ship;
	CollisionObject* shipCollision;
	SmartAnimationSequenceNode* smokeAnimation;
	SmartAnimationSequenceNode* shipFireAnimation;
	SmartAnimationSequenceNode* fireAnimation;
	SmartAnimationSequenceNode* thrustAnimation;
	SmartAnimationSequenceNode* explodeAnimation;
	SmartAnimationSequenceNode* fireRingAnimation;
	SmartAnimationSequenceNode* groundFireAnimation;
	SmartAnimationSequenceNode* groundFireSmallAnimation;
	KSequence* skipSequence;

	Sound* lightningSound;
	Sound* thrusterSound;
	Sound* enterAtmosphereSound;
	Sound* crashSound;
	Sound* fireSound;
};
