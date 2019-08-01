#include "QuestEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string QuestEvents::EventQuestTaskComplete = "EVENT_QUEST_TASK_COMPLETE";

void QuestEvents::TriggerQuestTaskComplete(QuestTaskCompleteArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		QuestEvents::EventQuestTaskComplete + args.questLine,
		&args
	);
}