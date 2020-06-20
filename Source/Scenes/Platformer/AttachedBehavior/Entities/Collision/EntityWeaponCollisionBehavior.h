#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehavior : public AttachedBehavior
{
public:
	void enable();
	void disable();
	
protected:
	EntityWeaponCollisionBehavior(GameObject* owner);
	virtual ~EntityWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void setWeaponCollisionSize(cocos2d::Size weaponCollisionSize);
	void setWeaponCollisionOffset(cocos2d::Vec2 weaponCollisionOffset);
	void rebuildWeaponCollision(int collisionType);

	CollisionObject* weaponCollision;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::Size weaponCollisionSize;
	cocos2d::Vec2 weaponCollisionOffset;

	static const cocos2d::Size DefaultWeaponSize;
};
