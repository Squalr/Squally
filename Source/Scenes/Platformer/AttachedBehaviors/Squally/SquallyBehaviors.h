#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyBehaviors : public AttachedBehaviorGroup
{
public:
	static SquallyBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
