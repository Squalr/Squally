#include "QuestEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string QuestEvents::EventQuestTaskComplete = "EVENT_QUEST_TASK_COMPLETE";

void QuestEvents::TriggerQuestTaskComplete(QuestTaskCompleteArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		QuestEvents::EventQuestTaskComplete + args.questLine,
		&args
	);
}