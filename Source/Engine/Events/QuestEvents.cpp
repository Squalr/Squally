#include "QuestEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string QuestEvents::EventAdvanceNextQuest = "EVENT_ADVANCE_NEXT_QUEST";
const std::string QuestEvents::EventAdvanceQuest = "EVENT_ADVANCE_QUEST";

void QuestEvents::TriggerAdvanceToNextQuest(AdvanceNextQuestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		QuestEvents::EventAdvanceNextQuest,
		&args
	);
}

void QuestEvents::TriggerAdvanceToQuest(AdvanceToQuestArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		QuestEvents::EventAdvanceQuest,
		&args
	);
}
