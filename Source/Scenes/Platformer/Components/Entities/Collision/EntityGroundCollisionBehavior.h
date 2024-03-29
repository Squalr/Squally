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
	bool isStandingOn(CollisionObject* collisonObject);
	bool isStandingOnSomethingOtherThan(CollisionObject* collisonObject);
	
	cocos2d::Vec2 defaultPosition;

	static const std::string MapKey;
	static const int DropShadowDetectorCount;
	static const float DropShadowPadding;
	static const float DropShadowCollisionHeight;
	static const float GroundCollisionPadding;
	static const float GroundCollisionOffset;
	static const float GroundCollisionHeight;

protected:
	EntityGroundCollisionBehavior(GameObject* owner);
	virtual ~EntityGroundCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef GameComponent super;

	void buildDropShadowCollisionDetector();
	void buildGroundCollisionDetector();

	struct DropShadowResult
	{
		cocos2d::Vec2 intersectionPoint;
		float slope = 0.0f;
		float dropDistance = 0.0f;
		bool isValid = false;
	};

	CollisionObject* groundCollision = nullptr;
	std::vector<CollisionObject*> dropShadowCollisions;
	PlatformerEntity* entity = nullptr;
	EntityHoverCollisionBehavior* hoverCollisionBehavior = nullptr;

	CollisionObject* currentGround = nullptr;
	float dropShadowOpacity = 0.0f;
	float dropShadowScale = 0.0f;
	float deathScaler = 0.0f;

	float detectorWidth = 0.0f;
};
