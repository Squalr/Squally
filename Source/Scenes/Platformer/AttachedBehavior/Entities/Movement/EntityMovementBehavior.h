#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityMovementBehavior : public AttachedBehavior
{
public:
	static EntityMovementBehavior* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;
	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float JumpVelocity;

protected:
	EntityMovementBehavior(GameObject* owner);
	virtual ~EntityMovementBehavior();

	void onLoad() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	bool isOnGround();
	void applyCinematicMovement(cocos2d::Vec2* movement);
	void applyPatrolMovement(cocos2d::Vec2* movement);
	void checkCinematicMovementComplete();
	void checkPatrolMovementComplete();

	PlatformerEntity* entity;
	cocos2d::Vec2 preCinematicPosition;
	cocos2d::Vec2 prePatrolPosition;
};
