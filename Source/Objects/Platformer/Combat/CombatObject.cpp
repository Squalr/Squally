#include "CombatObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Events/CombatEvents.h"

using namespace cocos2d;

CombatObject::CombatObject(PlatformerEntity* caster, PlatformerEntity* target, bool onTimeline)
	: super()
{
	this->caster = caster;
	this->target = target;
	this->timelinePaused = false;
	this->timelinePausedCinematic = false;
	this->canUpdate = true;
	this->onTimeline = onTimeline;
}

CombatObject::~CombatObject()
{
}

void CombatObject::onEnter()
{
	super::onEnter();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimeline, [=](EventCustom* eventCustom)
	{
		this->timelinePaused = true;
		
		this->updateObjectCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimeline, [=](EventCustom* eventCustom)
	{
		this->timelinePaused = false;
		
		this->updateObjectCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventPauseTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->timelinePausedCinematic = true;
		
		this->updateObjectCanUpdate();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventResumeTimelineCinematic, [=](EventCustom* eventCustom)
	{
		this->timelinePausedCinematic = false;

		this->updateObjectCanUpdate();
	}));
}

void CombatObject::update(float dt)
{
	super::update(dt);
	
	if (!this->canUpdate)
	{
		return;
	}
}

void CombatObject::enableUpdate()
{
	this->canUpdate = true;
}

void CombatObject::disableUpdate()
{
	this->canUpdate = false;
}
	
void CombatObject::updateObjectCanUpdate()
{
	if (this->onTimeline)
	{
		if (this->timelinePaused || this->timelinePausedCinematic)
		{
			this->disableUpdate();
		}
		else
		{
			this->enableUpdate();
		}
	}
}
