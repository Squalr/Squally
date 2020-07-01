#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class EntityCollisionBehaviorBase;
class EntityGroundCollisionBehavior;
class EntityJumpCollisionBehavior;
class PlatformerEntity;

class EntityHoverCollisionBehavior : public AttachedBehavior
{
public:
	static EntityHoverCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	EntityHoverCollisionBehavior(GameObject* owner);
	virtual ~EntityHoverCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	void crouch(float dt);
	void uncrouch(float dt);
	void rebuildHoverCrouchCollision();
	cocos2d::Size getHoverSize(float progress = 1.0f);
	void positionHoverCollision(float progress = 1.0f);

	float crouchProgress;

	PlatformerEntity* entity;
	CollisionObject* hoverCollision;
	CollisionObject* hoverAntiGravityCollisionDetector;

	EntityCollisionBehaviorBase* entityCollision;
	EntityGroundCollisionBehavior* groundCollision;
	EntityJumpCollisionBehavior* jumpCollision;

	void buildHoverAntiGravityCollision();
	void buildHoverCollision();
};
