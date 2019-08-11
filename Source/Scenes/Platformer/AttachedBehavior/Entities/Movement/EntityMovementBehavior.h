#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class PlatformerEntity;

class EntityMovementBehavior : public AttachedBehavior
{
public:
	static EntityMovementBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;
	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float JumpVelocity;

protected:
	EntityMovementBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityMovementBehavior();

	void onLoad() override;
	void update(float dt) override;
	
	cocos2d::Vec2 movement;

private:
	typedef AttachedBehavior super;

	bool isOnGround();

	PlatformerEntity* entity;
};
