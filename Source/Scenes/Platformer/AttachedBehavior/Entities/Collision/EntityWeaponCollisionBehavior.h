#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class CollisionObject;
class PlatformerEntity;

class EntityWeaponCollisionBehavior : public AttachedBehavior
{
public:
	static EntityWeaponCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	void enable();
	void disable();
	void setWeaponSize(cocos2d::Size weaponSize);
	void setWeaponOffset(cocos2d::Vec2 weaponOffset);
	void rebuildWeaponCollision();

	CollisionObject* weaponCollision;

	static const std::string MapKeyAttachedBehavior;

protected:
	EntityWeaponCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~EntityWeaponCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	PlatformerEntity* entity;

	cocos2d::Size weaponSize;
	cocos2d::Vec2 weaponOffset;

	static const cocos2d::Size DefaultWeaponSize;
};
