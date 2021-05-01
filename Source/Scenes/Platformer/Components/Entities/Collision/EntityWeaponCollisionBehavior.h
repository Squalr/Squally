#pragma once

#include "Engine/Components/Component.h"

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehavior : public Component
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
	typedef Component super;

	PlatformerEntity* entity;

	cocos2d::Size weaponCollisionSize;
	cocos2d::Vec2 weaponCollisionOffset;

	static const cocos2d::Size DefaultWeaponSize;
};
