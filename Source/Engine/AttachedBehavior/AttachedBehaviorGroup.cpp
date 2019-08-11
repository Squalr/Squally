#include "AttachedBehaviorGroup.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Quests/Quests.h"

using namespace cocos2d;

AttachedBehaviorGroup::AttachedBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs, std::vector<AttachedBehavior*> attachedBehavior) : super(owner, attachedBehaviorArgs)
{
	for (auto it = attachedBehavior.begin(); it != attachedBehavior.end(); it++)
	{
		owner->attachBehavior(*it);
	}
}

AttachedBehaviorGroup::~AttachedBehaviorGroup()
{
}
