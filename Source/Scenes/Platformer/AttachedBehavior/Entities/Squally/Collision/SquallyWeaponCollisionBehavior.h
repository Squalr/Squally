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

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyWeaponCollisionBehavior(GameObject* owner);
	~SquallyWeaponCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void onWeaponChange();

	Squally* squally;
};
