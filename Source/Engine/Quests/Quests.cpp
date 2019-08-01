#include "Quests.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string Quests::QuestsSaveKey = "SAVE_KEY_QUESTS";

Quests::Quests()
{
}

Quests::~Quests()
{
}

ValueMap Quests::getQuestData()
{
	return SaveManager::getProfileDataOrDefault(Quests::QuestsSaveKey, Value(ValueMap())).asValueMap();
}

std::string Quests::getCurrentQuestTaskForLine(std::string questLine)
{
	ValueMap questData = Quests::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString();
	}

	return "";
}

std::set<std::string> Quests::getStartedQuestLines()
{
	std::set<std::string> questLines = std::set<std::string>();

	ValueMap questData = Quests::getQuestData();

	for (auto it = questData.begin(); it != questData.end(); it++)
	{
		questLines.insert((*it).first);
	}

	return questLines;
}

std::set<std::string> Quests::getActiveQuestLines()
{
	// TODO
	return Quests::getStartedQuestLines();
}

std::set<std::string> Quests::getCompletedQuestLines()
{
	// TODO
	return Quests::getStartedQuestLines();
}
