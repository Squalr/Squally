#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class EntityCollisionBehaviorBase;
class EntityGroundCollisionBehavior;
class PlatformerEntity;

class EntityHoverCollisionBehavior : public AttachedBehavior
{
public:
	static EntityHoverCollisionBehavior* create(GameObject* owner);

	bool canJump();
	bool isOnGround();

	static const std::string MapKey;

protected:
	EntityHoverCollisionBehavior(GameObject* owner);
	virtual ~EntityHoverCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;
	CollisionObject* hoverCollision;
	CollisionObject* hoverGroundCollisionDetector;
	CollisionObject* hoverJumpCollisionDetector;

	EntityCollisionBehaviorBase* entityCollision;
	EntityGroundCollisionBehavior* groundCollision;

	void buildHoverGroundCollision();
	void buildHoverJumpCollision();
	void buildHoverCollision();
};
