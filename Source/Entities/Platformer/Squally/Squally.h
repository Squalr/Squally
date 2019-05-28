#pragma once

#include "Entities/Platformer/PlatformerFriendly.h"

namespace cocos2d
{
	typedef std::map<std::string, Value> ValueMap;
}

class CollisionObject;

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

	cocos2d::Vec2 getButtonOffset() override;

private:
	typedef PlatformerFriendly super;
	Squally(cocos2d::ValueMap& properties);
	virtual ~Squally();

	void onEnter() override;
	void onEnterTransitionDidFinish() override;
	void onExit() override;
	void initializePositions() override;
	void update(float) override;
	void onHackerModeEnable() override;
	void saveState();
	void loadState();
	void updateWeaponVisual();

	bool canJump;
	float noCombatDuration;

	cocos2d::Node* cameraTrackTarget;

	static const float squallyScale;
};
