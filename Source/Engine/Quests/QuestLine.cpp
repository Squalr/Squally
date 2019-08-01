#include "QuestLine.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Quests/Quests.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE";

QuestLine::QuestLine(std::string questLine, const std::map<std::string, std::tuple<bool, std::function<QuestTask*(GameObject*, QuestLine*, std::string)>>> quests)
{
	this->questLine = questLine;
	this->quests = quests;
}

QuestLine::~QuestLine()
{
}

QuestTask* QuestLine::deserialize(GameObject* owner, std::string questTask, std::string questTag)
{
	if (this->quests.find(questTask) != this->quests.end())
	{
		return std::get<1>(this->quests.at(questTask))(owner, this, questTag);
	}

	return nullptr;
}

const std::vector<QuestLine::QuestData> QuestLine::getQuests()
{
	std::vector<QuestData> questData = std::vector<QuestData>();
	std::string currentQuestTask = Quests::getCurrentQuestTaskForLine(this->questLine);
	bool hasEncounteredActive = false;
	bool activeThroughSkippable = false;

	for (auto it = this->quests.begin(); it != this->quests.end(); it++)
	{
		bool isActive = activeThroughSkippable || (*it).first == currentQuestTask;
		bool isComplete = !isActive && hasEncounteredActive;
		bool isSkippable = std::get<0>((*it).second);

		questData.push_back(QuestData((*it).first, isActive, isSkippable, isComplete));

		if (activeThroughSkippable || isActive)
		{
			activeThroughSkippable &= isSkippable;
		}

		hasEncounteredActive |= isActive;
	}

	return questData;
}

std::string QuestLine::getQuestLine()
{
	return this->questLine;
}

std::string QuestLine::getActiveQuestTaskName()
{
	ValueMap questData = Quests::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString();
	}

	return "";
}

bool QuestLine::isQuestTaskComplete(std::string questTask)
{
	ValueMap questData = Quests::getQuestData();

	if (questData.find(questLine) != questData.end())
	{
		return questData[questLine].asString() == QuestLine::QuestLineSaveKeyComplete;
	}

	return false;
}

LocalizedString* QuestLine::getQuestLineName()
{
	return nullptr;
}

LocalizedString* QuestLine::getQuestLineObjective(std::string questTask)
{
	return nullptr;
}

void QuestLine::advanceNextQuest(QuestTask* currentQuest)
{
	QuestEvents::TriggerQuestTaskComplete(QuestEvents::QuestTaskCompleteArgs(this->questLine, currentQuest));
}

void QuestLine::markQuestLineComplete()
{
}
