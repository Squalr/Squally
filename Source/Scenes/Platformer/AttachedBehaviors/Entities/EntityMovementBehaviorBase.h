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
protected:
	EntityMovementBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityMovementBehaviorBase();

	void update(float dt) override;
	void onLoad() override;
	
	cocos2d::Vec2 movement;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
