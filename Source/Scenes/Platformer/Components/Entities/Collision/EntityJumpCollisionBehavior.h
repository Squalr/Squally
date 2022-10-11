#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class EntityHoverCollisionBehavior;
class PlatformerEntity;

class EntityJumpCollisionBehavior : public GameComponent
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
	typedef GameComponent super;

	void buildJumpCollisionDetector();
	
	CollisionObject* jumpCollision = nullptr;
	PlatformerEntity* entity = nullptr;
	EntityHoverCollisionBehavior* hoverCollisionBehavior = nullptr;
};
