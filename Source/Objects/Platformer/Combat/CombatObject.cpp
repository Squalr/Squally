#include "CombatObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Events/CombatEvents.h"

using namespace cocos2d;

CombatObject::CombatObject(PlatformerEntity* caster, PlatformerEntity* owner, bool onTimeline)
	: super()
{
	this->caster = caster;
	this->owner = owner;
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

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventBuffTimeElapsed, [=](EventCustom* eventCustom)
	{
		CombatEvents::BuffTimeElapsedArgs* args = static_cast<CombatEvents::BuffTimeElapsedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->elapse(args->dt);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyTimelineSpeed, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableTimelineSpeedArgs* args = static_cast<CombatEvents::ModifiableTimelineSpeedArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled())
		{
			this->onModifyTimelineSpeed(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeDamageDelt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityModifyDamageDeltComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onAfterDamageDelt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeDamageTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityModifyDamageTakenComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onAfterDamageTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeHealingDelt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeHealingTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityTimelineReset, [=](EventCustom* eventCustom)
	{
		CombatEvents::TimelineResetArgs* args = static_cast<CombatEvents::TimelineResetArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->onTimelineReset(args);
		}
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

void CombatObject::elapse(float dt)
{
}

void CombatObject::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
}

void CombatObject::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onAfterDamageDelt(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onTimelineReset(CombatEvents::TimelineResetArgs* timelineReset)
{
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
