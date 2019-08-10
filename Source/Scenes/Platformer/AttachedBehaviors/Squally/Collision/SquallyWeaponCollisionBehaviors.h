#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class PlatformerEnemy;
class Squally;

class SquallyWeaponCollisionBehaviors : public AttachedBehavior
{
public:
	static SquallyWeaponCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyWeaponCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyWeaponCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	void onWeaponChange();

	Squally* squally;
};
