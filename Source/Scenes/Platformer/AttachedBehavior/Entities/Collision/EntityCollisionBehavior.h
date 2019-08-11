#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityCollisionBehavior : public AttachedBehavior
{
public:
	static EntityCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);
	
	CollisionObject* entityCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
