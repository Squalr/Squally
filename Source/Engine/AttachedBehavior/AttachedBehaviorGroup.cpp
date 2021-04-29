#include "AttachedBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"

using namespace cocos2d;

AttachedBehaviorGroup::AttachedBehaviorGroup(GameObject* owner, std::vector<AttachedBehavior*> attachedBehavior) : super(owner)
{
	for (auto next : attachedBehavior)
	{
		owner->attachBehavior(next);
	}
}

AttachedBehaviorGroup::~AttachedBehaviorGroup()
{
}
