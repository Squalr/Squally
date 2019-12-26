#include "QuestTask.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Quests/Quests.h"

using namespace cocos2d;

QuestTask::QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, bool skippable) : super()
{
	this->questState = QuestState::None;
	this->owner = owner;
	this->questLine = questLine;
	this->questTask = questTask;
	this->isSkippable = skippable;
	this->hasLoaded = false;
	this->completeCalled = false;

	this->addChild(this->questLine);
}

QuestTask::~QuestTask()
{
}

void QuestTask::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->updateState();
}

void QuestTask::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventQuestTaskComplete + this->questLine->getQuestLine(), [=](EventCustom* eventCustom)
	{
		QuestEvents::QuestTaskCompleteArgs* args = static_cast<QuestEvents::QuestTaskCompleteArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && this->questLine != nullptr && args->questLine == this->questLine->getQuestLine())
		{
			this->updateState();
		}
	}));
}

std::string QuestTask::getQuestTaskName()
{
	return this->questTask;
}

QuestTask::QuestState QuestTask::getQuestState()
{
	return this->questState;
}

QuestTask::QuestState QuestTask::getQuestStateForTask(QuestLine* questLine, std::string questTask)
{
	const std::vector<QuestLine::QuestMeta> quests = questLine->getQuests();
	
	bool isPreviousSkippable = false;
	bool isPreviousComplete = false;
	QuestState questState = QuestState::None;

	for (auto it = quests.begin(); it != quests.end(); it++)
	{
		if ((*it).questTask == questTask)
		{
			if ((*it).isComplete)
			{
				questState = QuestState::Complete;
			}
			else if ((*it).isActive && (isPreviousSkippable && !isPreviousComplete))
			{
				questState = QuestState::ActiveThroughSkippable;
			}
			else if ((*it).isActive)
			{
				questState = QuestState::Active;
			}
			
			break;
		}

		isPreviousSkippable = (*it).isSkippable;
		isPreviousComplete = (*it).isComplete;
	}

	return questState;
}

void QuestTask::updateState()
{
	QuestState previousState = this->questState;
	this->questState = QuestTask::getQuestStateForTask(this->questLine, this->questTask);

	if (!this->hasLoaded)
	{
		this->hasLoaded = true;
		this->onLoad(this->questState);
	}

	if (previousState == QuestState::None)
	{
		if (this->questState == QuestState::Active)
		{
			this->onActivate(false);
		}
		else if (this->questState == QuestState::ActiveThroughSkippable)
		{
			this->onActivate(true);
		}
	}

	// Check if this quest was skipped
	if (!this->completeCalled && previousState == QuestState::ActiveThroughSkippable && (this->questState == QuestState::None || this->questState == QuestState::Complete))
	{
		this->onSkipped();
	}
}

bool QuestTask::isActive()
{
	return this->questState == QuestState::Active || this->questState == QuestState::ActiveThroughSkippable;
}

void QuestTask::complete()
{
	// Ideally we would also check to see if this quest is active, but we'll leave it up to the caller instead to
	// ensure complete() is never called in such a way to sequence break. Allowing sequence breaks makes debugging easier anyhow.
	if (this->completeCalled || this->questState == QuestState::Complete)
	{
		return;
	}

	this->completeCalled = true;
	this->questState = QuestState::Complete;

	this->onComplete();

	this->questLine->advanceNextQuest(this);
}
