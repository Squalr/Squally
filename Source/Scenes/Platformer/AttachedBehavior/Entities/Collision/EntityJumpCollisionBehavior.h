#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityJumpCollisionBehavior : public AttachedBehavior
{
public:
	static EntityJumpCollisionBehavior* create(GameObject* owner);

	bool canJump();
	
	CollisionObject* jumpCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityJumpCollisionBehavior(GameObject* owner);
	virtual ~EntityJumpCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef AttachedBehavior super;

	void buildJumpCollisionDetector();

	PlatformerEntity* entity;

	static const float JumpCollisionMargin;
	static const float JumpCollisionOffset;
	static const float JumpCollisionHeight;
};
