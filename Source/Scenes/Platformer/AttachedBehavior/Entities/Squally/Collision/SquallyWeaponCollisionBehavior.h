#pragma once

#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyWeaponCollisionBehavior : public EntityWeaponCollisionBehavior
{
public:
	static SquallyWeaponCollisionBehavior* create(GameObject* owner);

	static const std::string MapKey;

protected:
	SquallyWeaponCollisionBehavior(GameObject* owner);
	virtual ~SquallyWeaponCollisionBehavior();

	void onLoad() override;
	void onDisable() override;

private:
	typedef EntityWeaponCollisionBehavior super;

	void onWeaponChange();

	bool canEngage;
	
	Squally* squally;
};
