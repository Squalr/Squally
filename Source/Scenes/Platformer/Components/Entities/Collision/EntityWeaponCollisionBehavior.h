#pragma once

#include "Engine/Components/GameComponent.h"

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehavior : public GameComponent
{
public:
	void enable();
	void disable();
	CollisionObject* getMainhandWeaponCollision() const;
	CollisionObject* getOffhandWeaponCollision() const;
	cocos2d::Vec2 getWeaponCollisionOffset() const;
	cocos2d::Vec2 getOffhandWeaponCollisionOffset() const;
	cocos2d::Vec2 getWeaponCollisionDebugOffset() const;
	cocos2d::Vec2 getOffhandWeaponCollisionDebugOffset() const;
	void setWeaponCollisionDebugOffset(cocos2d::Vec2 weaponCollisionDebugOffset);
	void setOffhandWeaponCollisionDebugOffset(cocos2d::Vec2 weaponCollisionDebugOffset);
	
protected:
	EntityWeaponCollisionBehavior(GameObject* owner);
	virtual ~EntityWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;
	void setWeaponCollisionSize(cocos2d::CSize weaponCollisionSize);
	void setWeaponCollisionOffset(cocos2d::Vec2 weaponCollisionOffset);
	void setOffhandWeaponCollisionSize(cocos2d::CSize weaponCollisionSize);
	void setOffhandWeaponCollisionOffset(cocos2d::Vec2 weaponCollisionOffset);
	void rebuildWeaponCollision(int collisionType, bool buildOffhand);
	void refreshWeaponCollisionOffsets();

	CollisionObject* mainhandWeaponCollision = nullptr;
	CollisionObject* offhandWeaponCollision = nullptr;

private:
	typedef GameComponent super;

	PlatformerEntity* entity = nullptr;

	cocos2d::CSize weaponCollisionSize;
	cocos2d::CSize offhandWeaponCollisionSize;
	cocos2d::Vec2 weaponCollisionOffset;
	cocos2d::Vec2 offhandWeaponCollisionOffset;
	cocos2d::Vec2 weaponCollisionDebugOffset;
	cocos2d::Vec2 offhandWeaponCollisionDebugOffset;
	bool useExplicitWeaponSize = false;
	bool useExplicitOffhandWeaponSize = false;

	static const cocos2d::CSize DefaultWeaponSize;
};
