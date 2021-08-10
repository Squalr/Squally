#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehavior : public GameComponent
{
public:
	void enable();
	void disable();
	
protected:
	EntityWeaponCollisionBehavior(GameObject* owner);
	virtual ~EntityWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void setWeaponCollisionSize(cocos2d::CSize weaponCollisionSize);
	void setWeaponCollisionOffset(cocos2d::Vec2 weaponCollisionOffset);
	void rebuildWeaponCollision(int collisionType);

	CollisionObject* weaponCollision;

private:
	typedef GameComponent super;

	PlatformerEntity* entity;

	cocos2d::CSize weaponCollisionSize;
	cocos2d::Vec2 weaponCollisionOffset;

	static const cocos2d::CSize DefaultWeaponSize;
};
