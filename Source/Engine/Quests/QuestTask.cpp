#include "QuestTask.h"

using namespace cocos2d;

QuestTask::QuestTask(GameObject* owner, std::string quest, bool skippable) : super()
{
	this->owner = owner;
	this->quest = quest;
	this->isActive = false;
	this->isSkippable = skippable;
	this->isComplete = false;
	this->hasActivated = false;
}

QuestTask::~QuestTask()
{
}

void QuestTask::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->onLoad(this->isQuestActive(), this->isQuestSkippable(), this->isQuestComplete());
}

void QuestTask::initializeListeners()
{
	super::initializeListeners();
}

void QuestTask::onActivateAsSkippable()
{
	this->onActivate();
}

void QuestTask::setActive(bool isActive)
{
	this->isActive = isActive;

	if (this->isActive && !this->hasActivated)
	{
		this->hasActivated = true;

		// Run activate function -- can only be run once
		this->onActivate();
	}
}

void QuestTask::setActiveThroughSkippable()
{
	if (!this->hasActivated)
	{
		this->hasActivated = true;

		this->onActivateAsSkippable();
	}
}

void QuestTask::markComplete()
{
	this->isComplete = true;
}

std::string QuestTask::getQuestName()
{
	return this->quest;
}

bool QuestTask::isQuestComplete()
{
	return this->isComplete;
}

bool QuestTask::isQuestActive()
{
	return this->isActive;
}

bool QuestTask::isQuestSkippable()
{
	return this->isSkippable;
}
