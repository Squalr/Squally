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
	static SquallyStatsBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	SquallyStatsBehaviorGroup(GameObject* owner);
	~SquallyStatsBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
