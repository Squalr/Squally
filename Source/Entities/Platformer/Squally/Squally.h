#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject;
class SmartAnimationSequenceNode;

class Squally : public PlatformerFriendly
{
public:
	static Squally* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;
	cocos2d::Vec2 getAvatarFrameOffset() override;

	void setEq(int eq);
	int getEq();
	void setEqExperience(int eqExperience);
	void addEqExperience(int eqExperience);
	int getEqExperience();

	static const std::string MapKeySqually;
	static const int SquallyBaseHealth;
	static const int SquallyBaseSpecial;

protected:
	void initializeCollisionEvents() override;
	void performSwimAnimation() override;

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	Squally(cocos2d::ValueMap& properties);
	virtual ~Squally();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void onHackerModeEnable() override;
	void registerHackables() override;
	bool isAliveSqually();
	void saveState();
	void loadState();
	void updateWeaponVisual();
	void runEyeBlinkLoop();

	bool canJump;
	float noCombatDuration;
	int eq;
	int eqExperience;

	cocos2d::Node* cameraTrackTarget;
	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	static const float SquallyScale;
	static const int DefaultEq;
	static const std::string IdentifierIsAlive;
	static const std::string EventSquallyTrapped;
};
