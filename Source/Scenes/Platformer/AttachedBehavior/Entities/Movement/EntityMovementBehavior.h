#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"


class EntityMovementCollisionBehavior;
class EntityGroundCollisionBehavior;
class EntityJumpCollisionBehavior;
class PlatformerEntity;
class WorldSound;

class EntityMovementBehavior : public AttachedBehavior
{
public:
	static EntityMovementBehavior* create(GameObject* owner);

	void setMoveAcceleration(float moveAcceleration);
	void setSwimAcceleration(cocos2d::Vec2 swimAcceleration);
	void setJumpVelocity(float jumpVelocity);

	void cancelWaterSfx();

	static const std::string MapKey;
	static const float DefaultWalkAcceleration;
	static const float DefaultRunAcceleration;
	static const cocos2d::Vec2 DefaultSwimAcceleration;
	static const float DefaultJumpVelocity;

protected:
	EntityMovementBehavior(GameObject* owner);
	virtual ~EntityMovementBehavior();

	void onLoad() override;
	void onDisable() override;
	void update(float dt) override;

private:
	typedef AttachedBehavior super;

	bool isOnGround();
	void applyCinematicMovement(cocos2d::Vec2* movement);
	void applyPatrolMovement(cocos2d::Vec2* movement);
	void checkCinematicMovementComplete();
	void checkPatrolMovementComplete();

	float moveAcceleration;
	cocos2d::Vec2 swimAcceleration;
	float jumpVelocity;

	PlatformerEntity* entity;
	cocos2d::Vec2 preCinematicPosition;
	cocos2d::Vec2 prePatrolPosition;

	WorldSound* jumpSound;
	std::vector<WorldSound*> swimSounds;
	std::vector<WorldSound*> walkSounds;
	
	EntityMovementCollisionBehavior* movementCollision;
	EntityGroundCollisionBehavior* groundCollision;
	EntityJumpCollisionBehavior* jumpBehavior;

	int swimSoundIndex;
	int walkSoundIndex;
};
