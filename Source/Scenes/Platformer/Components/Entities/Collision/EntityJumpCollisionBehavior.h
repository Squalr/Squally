#pragma once

#include "Engine/Components/Component.h"

class CollisionObject;
class EntityHoverCollisionBehavior;
class PlatformerEntity;

class EntityJumpCollisionBehavior : public Component
{
public:
	static EntityJumpCollisionBehavior* create(GameObject* owner);

	CollisionObject* getJumpCollision();
	bool canJump();

	static const std::string MapKey;
	static const float JumpCollisionMargin;
	static const float JumpCollisionOffset;
	static const float JumpCollisionHeight;

protected:
	EntityJumpCollisionBehavior(GameObject* owner);
	virtual ~EntityJumpCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef Component super;

	void buildJumpCollisionDetector();
	
	CollisionObject* jumpCollision;
	PlatformerEntity* entity;
	EntityHoverCollisionBehavior* hoverCollisionBehavior;
};
