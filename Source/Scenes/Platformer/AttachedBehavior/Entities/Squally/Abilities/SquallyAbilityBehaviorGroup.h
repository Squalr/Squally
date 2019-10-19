#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyAbilityBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyAbilityBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyAbilityBehaviorGroup(GameObject* owner);
	~SquallyAbilityBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
