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
	void setWeaponSize(cocos2d::Size weaponSize);
	void setWeaponOffset(cocos2d::Vec2 weaponOffset);
	void rebuildWeaponCollision(int collisionType);

	CollisionObject* weaponCollision;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::Size weaponSize;
	cocos2d::Vec2 weaponOffset;

	static const cocos2d::Size DefaultWeaponSize;
};
