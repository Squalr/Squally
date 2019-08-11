#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class SquallyStatsBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static SquallyStatsBehaviorGroup* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyStatsBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs);
	~SquallyStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
