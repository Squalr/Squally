#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyWeaponCollisionBehavior : public AttachedBehavior
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
	typedef AttachedBehavior super;

	void onWeaponChange();

	Squally* squally;
};
