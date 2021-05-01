#pragma once

#include "Engine/Components/Component.h"

class CollisionObject;
class EntityHoverCollisionBehavior;
class PlatformerEntity;

class EntityGroundCollisionBehavior : public Component
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
	typedef Component super;

	void buildGroundCollisionDetector();
	void buildCornerCollisionDetectors();

	CollisionObject* leftCornerCollision;
	CollisionObject* rightCornerCollision;
	CollisionObject* groundCollision;
	PlatformerEntity* entity;
	EntityHoverCollisionBehavior* hoverCollisionBehavior;

	float detectorWidth;
};
