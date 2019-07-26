#include "QuestLine.h"

#include "cocos/base/CCValue.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestTask.h"
#include "Engine/Save/SaveManager.h"

using namespace cocos2d;

const std::string QuestLine::QuestLineSaveKeyPrefix = "SAVE_KEY_QUEST_LINE_";
const std::string QuestLine::QuestLineSaveKeyComplete = "COMPLETE";

QuestLine::QuestLine(std::string questLine, std::vector<QuestTask*> questTasks)
{
	this->questLine = questLine;
	this->questTasks = questTasks;
	this->activeQuestTask = questTasks.size() > 0 ? questTasks.front() : nullptr;

	std::string savedQuestName = SaveManager::getProfileDataOrDefault(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value("")).asString();

	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		if ((*it)->getQuestName() == savedQuestName)
		{
			this->activeQuestTask = *it;

			for (auto innerIt = this->questTasks.begin(); innerIt != it; innerIt++)
			{
				// Assume everything up to the current quest is complete
				(*innerIt)->markComplete();
			}

			break;
		}
	}

	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		this->addChild(*it);
	}
}

QuestLine::~QuestLine()
{
}

void QuestLine::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	if (this->activeQuestTask != nullptr)
	{
		this->activeQuestTask->setActive(true);

		bool isPreviousSkippable = this->activeQuestTask->isQuestSkippable();

		// If the current quest task is skippable, mark the next quest task(s) as "active-through-skippable"
		for (auto it = std::find(this->questTasks.begin(), this->questTasks.end(), this->activeQuestTask) + 1; it != this->questTasks.end(); it++)
		{
			if (isPreviousSkippable)
			{
				(*it)->setActiveThroughSkippable();
				isPreviousSkippable = (*it)->isQuestSkippable();
			}
			else
			{
				break;
			}
		}
	}
}

void QuestLine::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventAdvanceNextQuestTask, [=](EventCustom* eventCustom)
	{
		QuestEvents::AdvanceNextQuestArgs* args = static_cast<QuestEvents::AdvanceNextQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->questTask == this->activeQuestTask)
		{
			this->advanceNextQuest(args->questTask);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventAdvanceQuestTask, [=](EventCustom* eventCustom)
	{
		QuestEvents::AdvanceToQuestArgs* args = static_cast<QuestEvents::AdvanceToQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->questLine == this->questLine)
		{
			this->advanceToQuest(args->newQuestTask);
		}
	}));
}

void QuestLine::advanceNextQuest(QuestTask* currentQuest)
{
	bool takeNext = currentQuest == nullptr;

	if (this->activeQuestTask != nullptr)
	{
		this->activeQuestTask->markComplete();
		this->activeQuestTask->setActive(false);
	}

	if (this->questTasks.empty() || this->activeQuestTask == this->questTasks.back())
	{
		this->markComplete();
		return;
	}

	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		if (takeNext)
		{
			this->activeQuestTask = *it;
			break;
		}

		if ((*it) == currentQuest)
		{
			takeNext = true;
		}
	}
	
	if (this->activeQuestTask != nullptr)
	{
		const std::string questName = this->activeQuestTask->getQuestName();

		SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(questName));

		this->activeQuestTask->setActive(true);
	}
}

void QuestLine::advanceToQuest(std::string questName)
{
	if (this->activeQuestTask != nullptr)
	{
		this->activeQuestTask->markComplete();
		this->activeQuestTask->setActive(false);
	}

	this->activeQuestTask = nullptr;

	// Advance to the quest with the given name
	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		const std::string nextQuestName = (*it)->getQuestName();

		if (nextQuestName == questName)
		{
			SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(questName));
			this->activeQuestTask = *it;
			this->activeQuestTask->setActive(true);
			return;
		}
	}

	// Fail safe
	if (this->activeQuestTask == nullptr)
	{
		this->markComplete();
	}
}

void QuestLine::markComplete()
{
	this->activeQuestTask = nullptr;
	SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(QuestLine::QuestLineSaveKeyComplete));
}
