#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class EntityHoverCollisionBehavior;
class PlatformerEntity;

class EntityGroundCollisionBehavior : public GameComponent
{
public:
	static EntityGroundCollisionBehavior* create(GameObject* owner);

	CollisionObject* getGroundCollision();
	void onCollideWithGround();
	bool isOnGround();
	bool hasLeftCornerCollision();
	bool hasRightCornerCollision();
	bool isStandingOn(CollisionObject* collisonObject);
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	
	cocos2d::Vec2 defaultPosition;

	static const std::string MapKey;
	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionHeight;
	static const float GroundCollisionRadius;
	static const float CornerCollisionWidth;

protected:
	EntityGroundCollisionBehavior(GameObject* owner);
	virtual ~EntityGroundCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef GameComponent super;

	void buildGroundCollisionDetector();
	void buildCornerCollisionDetectors();

	CollisionObject* leftCornerCollision = nullptr;
	CollisionObject* rightCornerCollision = nullptr;
	CollisionObject* groundCollision = nullptr;
	PlatformerEntity* entity = nullptr;
	EntityHoverCollisionBehavior* hoverCollisionBehavior = nullptr;

	float detectorWidth = 0.0f;
};
