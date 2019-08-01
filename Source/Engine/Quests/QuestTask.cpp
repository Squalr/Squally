#include "QuestTask.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/QuestEvents.h"

using namespace cocos2d;

QuestTask::QuestTask(GameObject* owner, std::string questLine, std::string questTask, std::string questTag, bool skippable) : super()
{
	this->questState = QuestState::Untracked;
	this->owner = owner;
	this->questLine = questLine;
	this->questTask = questTask;
	this->questTag = questTag;
	this->isSkippable = skippable;
	this->hasRunActivateFunction = false;
}

QuestTask::~QuestTask()
{
}

void QuestTask::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(QuestEvents::EventSkipQuestTask, [=](EventCustom* eventCustom)
	{
		QuestEvents::SkipQuestArgs* args = static_cast<QuestEvents::SkipQuestArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && args->questTask->getQuestLine() == this->getQuestLine() && args->questTask->getQuestName() == this->getQuestName())
		{
			this->skip();
		}
	}));
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

void QuestTask::onLoad(QuestTask::QuestState questState)
{
	switch (questState)
	{
		case QuestTask::QuestState::Active:
		{
			this->enable(false);
			break;
		}
		case QuestTask::QuestState::ActiveThroughSkippable:
		{
			this->enable(true);
			break;
		}
		default:
		{
			this->disable();
			break;
		}
	}
}

std::string QuestTask::getQuestLine()
{
	return this->questLine;
}

std::string QuestTask::getQuestName()
{
	return this->questTask;
}

bool QuestTask::isQuestSkippable()
{
	return this->isSkippable;
}

void QuestTask::skip()
{
	switch(this->questState)
	{
		case QuestState::Active:
		case QuestState::ActiveThroughSkippable:
		{
			this->setQuestState(QuestTask::QuestState::Untracked);
			this->disable();
			break;
		}
		default:
		{
			break;
		}
	}
}
