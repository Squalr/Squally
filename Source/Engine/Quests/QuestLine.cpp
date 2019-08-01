#include "QuestLine.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string QuestLine::QuestsSaveKey = "SAVE_KEY_QUESTS";
const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE";

ValueMap QuestLine::getQuestData()
{
	return SaveManager::getProfileDataOrDefault(QuestLine::QuestsSaveKey, Value(ValueMap())).asValueMap();
}

std::set<std::string> QuestLine::getQuestLines()
{
	std::set<std::string> questLines = std::set<std::string>();

	ValueMap questData = QuestLine::getQuestData();

	for (auto it = questData.begin(); it != questData.end(); it++)
	{
		questLines.insert((*it).first);
	}

	return questLines;
}

std::set<std::string> QuestLine::getActiveQuestLines()
{
	std::set<std::string> questLines = std::set<std::string>();

	ValueMap questData = QuestLine::getQuestData();

	for (auto it = questData.begin(); it != questData.end(); it++)
	{
		if ((*it).second.asString() != QuestLine::QuestLineSaveKeyComplete)
		{
			questLines.insert((*it).first);
		}
	}

	return questLines;
}

std::string QuestLine::getActiveQuestTaskForLine(std::string questLine)
{
	ValueMap questData = QuestLine::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString();
	}

	return "";
}

bool QuestLine::isQuestTaskComplete(std::string questLine, std::string questTask)
{
	ValueMap questData = QuestLine::getQuestData();

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
