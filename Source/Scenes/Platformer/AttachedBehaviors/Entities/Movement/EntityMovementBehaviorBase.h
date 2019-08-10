#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEntity;

class EntityMovementBehaviorBase : public AttachedBehavior
{
public:
	static const float MoveAcceleration;
	static const cocos2d::Vec2 SwimAcceleration;
	static const float JumpVelocity;

protected:
	EntityMovementBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityMovementBehaviorBase();

	void onLoad() override;
	void update(float dt) override;
	
	cocos2d::Vec2 movement;

private:
	typedef AttachedBehavior super;

	bool isOnGround();

	PlatformerEntity* entity;
};
