#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

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
	void performSwimAnimation() override;

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	friend class SquallyBehaviors;
	friend class SquallyCollisionBehaviors;
	friend class SquallyEquipmentVisualBehaviors;
	friend class SquallyMovementBehaviors;
	friend class SquallyOutOfCombatAttackBehaviors;
	
	Squally(cocos2d::ValueMap& properties);
	virtual ~Squally();
	
	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onHackerModeEnable(int eq) override;
	void saveState();
	void loadState();
	void runEyeBlinkLoop();
	void spawnHelper();

	bool canJump;

	cocos2d::Node* cameraTrackTarget;

	static const float SquallyScale;
};
