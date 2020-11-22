#include "CombatObject.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Events/CombatEvents.h"

using namespace cocos2d;

ValueMap CombatObject::HackStateStorage = ValueMap();

CombatObject::CombatObject(PlatformerEntity* caster, PlatformerEntity* owner, bool onTimeline, float duration)
	: super()
{
	this->caster = caster;
	this->owner = owner;
	this->timelinePaused = false;
	this->timelinePausedCinematic = false;
	this->canUpdate = true;
	this->onTimeline = onTimeline;
	this->duration = duration;
	this->elapsedDuration = 0.0f;
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
		CombatEvents::BuffTimeElapsedArgs* args = static_cast<CombatEvents::BuffTimeElapsedArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->elapse(args->dt);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyTimelineSpeed, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableTimelineSpeedArgs* args = static_cast<CombatEvents::ModifiableTimelineSpeedArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			this->onModifyTimelineSpeed(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyDamageDealt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeDamageDealt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyDamageDealtComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->onAfterDamageDealt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeDamageTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyDamageTakenComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->onAfterDamageTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyHealingDealt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeHealingDealt(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventModifyHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getData());

		if (args != nullptr && !args->isHandled())
		{
			this->onBeforeHealingTaken(args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityTimelineReset, [=](EventCustom* eventCustom)
	{
		CombatEvents::TimelineResetArgs* args = static_cast<CombatEvents::TimelineResetArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->onTimelineReset(args);
		}
	}));
}

void CombatObject::update(float dt)
{
	super::update(dt);

	if (!this->onTimeline)
	{
		this->updateDuration(dt);
	}
	
	if (!this->canUpdate)
	{
		return;
	}
}

void CombatObject::elapse(float dt)
{
	if (this->onTimeline)
	{
		this->updateDuration(dt);
	}
}

void CombatObject::updateDuration(float dt)
{
	this->elapsedDuration += dt;

	if (this->duration > 0.0f && this->elapsedDuration >= this->duration)
	{
		this->despawn();
	}
}

void CombatObject::onModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs* speed)
{
}

void CombatObject::onBeforeDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeDamageDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onAfterDamageTaken(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onAfterDamageDealt(CombatEvents::DamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
{
}

void CombatObject::onBeforeHealingDealt(CombatEvents::ModifiableDamageOrHealingArgs* damageOrHealing)
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
