#include "QuestTask.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"
#include "Engine/Quests/QuestLine.h"
#include "Engine/Quests/Quests.h"

using namespace cocos2d;

QuestTask::QuestTask(GameObject* owner, QuestLine* questLine, std::string questTask, std::string questTag, bool skippable) : super()
{
	this->questState = QuestState::None;
	this->owner = owner;
	this->questLine = questLine;
	this->questTask = questTask;
	this->questTag = questTag;
	this->isSkippable = skippable;
	this->hasLoaded = false;

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
		
		if (args != nullptr)
		{
			this->updateState();
		}
	}));
}

std::string QuestTask::getQuestTaskName()
{
	return this->questTask;
}

void QuestTask::updateState()
{
	const std::vector<QuestLine::QuestData> quests = this->questLine->getQuests();

	bool isPreviousSkippable = false;
	bool isPreviousComplete = false;
	QuestState previousState = this->questState;
	this->questState = QuestState::None;

	for (auto it = quests.begin(); it != quests.end(); it++)
	{
		if ((*it).questTask == this->questTask)
		{
			if ((*it).isComplete)
			{
				this->questState = QuestState::Complete;
			}
			else if ((*it).isActive && (isPreviousSkippable && !isPreviousComplete))
			{
				this->questState = QuestState::ActiveThroughSkippable;
			}
			else if ((*it).isActive)
			{
				this->questState = QuestState::Active;
			}
			
			break;
		}

		isPreviousSkippable = (*it).isSkippable;
		isPreviousComplete = (*it).isComplete;
	}

	if (!this->hasLoaded)
	{
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
}

bool QuestTask::isActive()
{
	return this->questState == QuestState::Active || this->questState == QuestState::ActiveThroughSkippable;
}

void QuestTask::complete()
{
	if (this->questState != QuestState::Active && this->questState != QuestState::ActiveThroughSkippable)
	{
		return;
	}

	this->questState = QuestState::Complete;

	this->onComplete();

	this->questLine->advanceNextQuest(this);
}
