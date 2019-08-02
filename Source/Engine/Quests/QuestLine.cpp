#include "QuestLine.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Quests/Quests.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE_";

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

	if (currentQuestTask.empty() && !this->quests.empty())
	{
		currentQuestTask = this->quests.begin()->first;
	}
	else if (StrUtils::startsWith(currentQuestTask, QuestLine::QuestLineSaveKeyComplete, false) && !this->quests.empty())
	{
		// Quest chain is (probably) completed. This may not be the case if we find that a new quest was added in a patch. Check for this.
		std::string lastKnownCompletedQuest = StrUtils::ltrim(currentQuestTask, QuestLine::QuestLineSaveKeyComplete, false);

		// If the last known completed quest doesn't match the end of the chain, a new quest was added
		if (lastKnownCompletedQuest != this->quests.end()->first)
		{
			for (auto it = this->quests.begin(); it != this->quests.end(); it++)
			{
				if ((*it).first == lastKnownCompletedQuest)
				{
					if (++it != this->quests.end())
					{
						// Set the current quest to the newly added next quest in the chain
						currentQuestTask = (*it).first;
					}

					break;
				}
			}
		}
	}

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
	if (currentQuest == nullptr)
	{
		return;
	}
	
	QuestEvents::TriggerQuestTaskComplete(QuestEvents::QuestTaskCompleteArgs(this->questLine, currentQuest));

	std::vector<QuestLine::QuestData> quests = this->getQuests();

	for (auto it = quests.begin(); it != quests.end(); it++)
	{
		std::string questTaskName = (*it).questTask;

		if (questTaskName == currentQuest->getQuestTaskName())
		{
			if (++it != quests.end())
			{
				// Progress to next task
				Quests::saveQuestLineProgress(this->questLine, (*it).questTask);
			}
			else
			{
				// Quest line complete
				Quests::saveQuestLineProgress(this->questLine, QuestLine::QuestLineSaveKeyComplete + questTaskName);
			}

			break;
		}
	}
}
