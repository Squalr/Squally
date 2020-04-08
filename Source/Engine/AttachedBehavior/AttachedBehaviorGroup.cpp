#include "AttachedBehaviorGroup.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Quests/Quests.h"

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
