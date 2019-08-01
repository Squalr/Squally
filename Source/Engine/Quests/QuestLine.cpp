#include "QuestLine.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Quests/Quests.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string QuestLine::QuestsSaveKey = "SAVE_KEY_QUESTS";
const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE";

QuestLine::QuestLine()
{
}

QuestLine::~QuestLine()
{
}

std::string QuestLine::getActiveQuestTaskForLine(std::string questLine)
{
	ValueMap questData = Quests::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString();
	}

	return "";
}

bool QuestLine::isQuestTaskComplete(std::string questLine, std::string questTask)
{
	ValueMap questData = Quests::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString() == QuestLine::QuestLineSaveKeyComplete;
	}

	return false;
}

LocalizedString* QuestLine::getQuestLineName(std::string questLine)
{
	return nullptr;
}

LocalizedString* QuestLine::getQuestLineObjective(std::string questLine, std::string questTask)
{
	return nullptr;
}

void QuestLine::advanceNextQuest(QuestTask* currentQuest)
{

}

void QuestLine::markQuestLineComplete(std::string questLine)
{

}
