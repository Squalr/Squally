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
	static SquallyWeaponCollisionBehavior* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyWeaponCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyWeaponCollisionBehavior();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void onWeaponChange();

	Squally* squally;
};
