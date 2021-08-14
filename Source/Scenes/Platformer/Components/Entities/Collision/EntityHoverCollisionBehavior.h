#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class EntityCollisionBehaviorBase;
class EntityGroundCollisionBehavior;
class EntityJumpCollisionBehavior;
class PlatformerEntity;

class EntityHoverCollisionBehavior : public GameComponent
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
	typedef GameComponent super;

	void crouch(float dt);
	void uncrouch(float dt);
	void rebuildHoverCrouchCollision();
	cocos2d::CSize getHoverSize(float progress = 1.0f);
	void positionHoverCollision(float progress = 1.0f);

	void buildHoverAntiGravityCollision();
	void buildHoverCollision();

	float crouchProgress = 0.0f;

	PlatformerEntity* entity = nullptr;
	CollisionObject* hoverCollision = nullptr;
	CollisionObject* hoverAntiGravityCollisionDetector = nullptr;
	CollisionObject* hoverAntiGravityTopCollisionDetector = nullptr;

	EntityCollisionBehaviorBase* entityCollision = nullptr;
	EntityGroundCollisionBehavior* groundCollision = nullptr;
	EntityJumpCollisionBehavior* jumpCollision = nullptr;
};
