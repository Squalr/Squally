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

QuestLine::QuestLine(std::string questLine, std::string quest, std::string questTag, std::vector<QuestTask*> questTasks)
{
	this->questLine = questLine;
	this->quest = quest;
	this->questTag = questTag;
	this->questTasks = questTasks;
	this->trackedQuestTask = nullptr;

	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		if ((*it)->getQuestName() == this->quest)
		{
			this->trackedQuestTask = *it;
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

	std::string savedQuestName = SaveManager::getProfileDataOrDefault(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value("")).asString();
	QuestTask* activeQuest = this->questTasks.empty() ? nullptr : this->questTasks.front();
	bool isPreviousSkippable = false;

	// Step 1: Locate the active quest
	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		if ((*it)->getQuestName() == savedQuestName)
		{
			activeQuest = *it;
			break;
		}
	}

	// Mark quests as either untracked (default), active, or active-through-skip
	for (auto it = std::find(this->questTasks.begin(), this->questTasks.end(), activeQuest); it != this->questTasks.end(); it++)
	{
		if (*it == this->trackedQuestTask && *it == activeQuest)
		{
			this->trackedQuestTask->setQuestState(QuestTask::QuestState::Active);
		}
		else if (*it == this->trackedQuestTask && isPreviousSkippable)
		{
			this->trackedQuestTask->setQuestState(QuestTask::QuestState::ActiveThroughSkippable);
		}
		else if (!(*it)->isQuestSkippable())
		{
			break;
		}

		isPreviousSkippable = (*it)->isQuestSkippable();
	}

	for (auto it = this->questTasks.begin(); it != this->questTasks.end(); it++)
	{
		(*it)->initialize();
	}
}

void QuestLine::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventAdvanceNextQuestTask, [=](EventCustom* eventCustom)
	{
		QuestEvents::AdvanceNextQuestArgs* args = static_cast<QuestEvents::AdvanceNextQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->questTask == this->trackedQuestTask)
		{
			this->advanceNextQuest(args->questTask);
		}
	}));
}

void QuestLine::advanceNextQuest(QuestTask* currentQuest)
{
	if (this->trackedQuestTask != nullptr)
	{
		this->trackedQuestTask->setQuestState(QuestTask::QuestState::Untracked);
	}

	for (auto it = std::find(this->questTasks.begin(), this->questTasks.end(), this->trackedQuestTask) + 1; it != this->questTasks.end(); it++)
	{
		QuestTask* newQuest = *it;
		SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(newQuest->getQuestName()));
		return;
	}

	this->markComplete();
}

void QuestLine::markComplete()
{
	if (this->trackedQuestTask != nullptr)
	{
		this->trackedQuestTask->setQuestState(QuestTask::QuestState::Untracked);
		this->trackedQuestTask = nullptr;
	}
	
	SaveManager::saveProfileData(QuestLine::QuestLineSaveKeyPrefix + this->questLine, Value(QuestLine::QuestLineSaveKeyComplete));
}
