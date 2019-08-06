#pragma once

#include "Engine/AttachedBehavior/AttachedBehavior.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyCollisionBehaviors : public AttachedBehavior
{
public:
	static SquallyCollisionBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyCollisionBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehavior super;

	Squally* squally;
};
