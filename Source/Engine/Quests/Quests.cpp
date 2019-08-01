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

std::set<std::string> Quests::getQuests()
{
	std::set<std::string> questLines = std::set<std::string>();

	ValueMap questData = Quests::getQuestData();

	for (auto it = questData.begin(); it != questData.end(); it++)
	{
		questLines.insert((*it).first);
	}

	return questLines;
}

std::set<std::string> Quests::getActiveQuests()
{
	std::set<std::string> questLines = std::set<std::string>();

	ValueMap questData = Quests::getQuestData();

	for (auto it = questData.begin(); it != questData.end(); it++)
	{
		//if ((*it).second.asString() != Quests::QuestsSaveKeyComplete)
		{
		//	questLines.insert((*it).first);
		}
	}

	return questLines;
}

