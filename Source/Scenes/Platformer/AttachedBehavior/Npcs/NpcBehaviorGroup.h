#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class NpcBehaviorGroup : public AttachedBehaviorGroup
{
public:
	static NpcBehaviorGroup* create(GameObject* owner);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcBehaviorGroup(GameObject* owner);
	~NpcBehaviorGroup();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
