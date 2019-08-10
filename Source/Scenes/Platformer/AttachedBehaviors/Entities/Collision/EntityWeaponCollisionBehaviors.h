#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehaviors : public AttachedBehavior
{
public:
	static EntityWeaponCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	void enable();
	void disable();
	void setWeaponSize(cocos2d::Size weaponSize);
	void setWeaponOffset(cocos2d::Vec2 weaponOffset);
	void rebuildWeaponCollision();
	
	CollisionObject* weaponCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityWeaponCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityWeaponCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::Size weaponSize;
	cocos2d::Vec2 weaponOffset;

	static const cocos2d::Size DefaultWeaponSize;
};
