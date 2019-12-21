#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyCollisionBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyCollisionBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyCollisionBehaviorGroup(GameObject* owner);
	~SquallyCollisionBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
