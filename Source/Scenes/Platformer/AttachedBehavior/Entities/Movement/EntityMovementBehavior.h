#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityMovementBehavior : public AttachedBehavior
{
public:
	static EntityMovementBehavior* create(GameObject* owner);

	void setMoveAcceleration(float moveAcceleration);
	void setSwimAcceleration(cocos2d::Vec2 swimAcceleration);
	void setJumpVelocity(float jumpVelocity);

	static const std::string MapKeyAttachedBehavior;
	static const float DefaultMoveAcceleration;
	static const cocos2d::Vec2 DefaultSwimAcceleration;
	static const float DefaultJumpVelocity;

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

	float moveAcceleration;
	cocos2d::Vec2 swimAcceleration;
	float jumpVelocity;

	PlatformerEntity* entity;
	cocos2d::Vec2 preCinematicPosition;
	cocos2d::Vec2 prePatrolPosition;
};
