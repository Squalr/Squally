#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"

class CollisionObject;
class PlatformerEntity;

class HelperCollisionBehavior : public EntityCollisionBehaviorBase
{
public:
	static HelperCollisionBehavior* create(GameObject* owner);

	CollisionObject* entityCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	HelperCollisionBehavior(GameObject* owner);
	virtual ~HelperCollisionBehavior();
	
	void onEntityCollisionCreated() override;

private:
	typedef EntityCollisionBehaviorBase super;
};
