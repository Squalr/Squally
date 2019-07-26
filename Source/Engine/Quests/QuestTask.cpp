#include "QuestTask.h"

using namespace cocos2d;

QuestTask::QuestTask(GameObject* owner, std::string quest, bool skippable) : super()
{
	this->questState = QuestState::Untracked;
	this->owner = owner;
	this->quest = quest;
	this->isSkippable = skippable;
	this->hasRunActivateFunction = false;
}

QuestTask::~QuestTask()
{
}

void QuestTask::initializeListeners()
{
	super::initializeListeners();
}

void QuestTask::initialize()
{
	if (!this->hasLoaded)
	{
		this->hasLoaded = true;
		this->onLoad(this->questState);
	}
}

QuestTask::QuestState QuestTask::getQuestState()
{
	return this->questState;
}

void QuestTask::setQuestState(QuestState questState)
{
	QuestState questStatePrevious = this->questState;
	this->questState = questState;

	if (!this->hasLoaded)
	{
		this->hasLoaded = true;
		this->onLoad(this->questState);
	}
	else
	{
		this->onStateChange(this->questState, questStatePrevious);
	}

	switch(this->questState)
	{
		case QuestState::Active:
		case QuestState::ActiveThroughSkippable:
		{
			if (!this->hasRunActivateFunction)
			{
				this->hasRunActivateFunction = true;
				this->onActivateRunOnce();
			}

			break;
		}
		default:
		{
			break;
		}
	}
}

std::string QuestTask::getQuestName()
{
	return this->quest;
}

bool QuestTask::isQuestSkippable()
{
	return this->isSkippable;
}
