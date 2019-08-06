#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject;
class PlatformerEnemy;
class SmartAnimationSequenceNode;

class Squally : public PlatformerFriendly
{
public:
	static Squally* deserialize(cocos2d::ValueMap& properties);

	float getFloatHeight() override;
	cocos2d::Vec2 getAvatarFrameOffset() override;

	static const std::string MapKeySqually;
	static const int SquallyBaseHealth;
	static const int SquallyBaseSpecial;

protected:
	void initializeCollisionEvents() override;
	void performSwimAnimation() override;
	std::string getOutOfCombatAttackAnimation() override;
	float getOutOfCombatAttackOnset() override;
	float getOutOfCombatAttackSustain() override;

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	Squally(cocos2d::ValueMap& properties);
	virtual ~Squally();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float) override;
	void onHackerModeEnable(int eq) override;
	void registerHackables() override;
	bool isAliveSqually();
	void engageEnemy(PlatformerEnemy* enemy, bool firstStrike);
	void saveState();
	void loadState();
	void rebuildWeaponCollision(cocos2d::Size size) override;
	void updateEquipmentVisual();
	void runEyeBlinkLoop();
	void spawnHelper();

	bool canJump;
	float noCombatDuration;

	cocos2d::Node* cameraTrackTarget;
	SmartAnimationSequenceNode* leftEyeController;
	SmartAnimationSequenceNode* rightEyeController;

	static const float SquallyScale;
	static const std::string IdentifierIsAlive;
	static const std::string EventSquallyTrapped;
};
