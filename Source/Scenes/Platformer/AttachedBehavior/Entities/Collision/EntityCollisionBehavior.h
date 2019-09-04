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
	static EntityCollisionBehavior* create(GameObject* owner);
	
	CollisionObject* entityCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityCollisionBehavior(GameObject* owner);
	~EntityCollisionBehavior();

	void update(float dt) override;
	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
};
