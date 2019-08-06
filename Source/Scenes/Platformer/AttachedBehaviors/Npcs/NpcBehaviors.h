#pragma once

#include "Engine/AttachedBehavior/AttachedBehaviorGroup.h"

namespace cocos2d
{
	class Sprite;
}

class Squally;

class NpcBehaviors : public AttachedBehaviorGroup
{
public:
	static NpcBehaviors* create(GameObject* owner, std::string attachedBehaviorArgs);

	static const std::string MapKeyAttachedBehavior;

protected:
	NpcBehaviors(GameObject* owner, std::string attachedBehaviorArgs);
	~NpcBehaviors();

	void onLoad() override;

private:
	typedef AttachedBehaviorGroup super;
};
