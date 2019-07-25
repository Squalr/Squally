#include "Buff.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Events/SceneEvents.h"
#include "Events/CombatEvents.h"

using namespace cocos2d;

Buff::Buff(PlatformerEntity* caster, PlatformerEntity* target)
{
	this->caster = caster;
	this->target = target;
	this->hackables = std::vector<HackableCode*>();
}

Buff::~Buff()
{
}

void Buff::onEnter()
{
	super::onEnter();

	this->registerHackables();
}

void Buff::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::BeforeSceneChangeEvent, [=](EventCustom* eventCustom)
	{
		this->unregisterHackables();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCombatFinished, [=](EventCustom* eventCustom)
	{
		this->removeBuff();
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageOrHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::BeforeDamageOrHealingDeltArgs* args = static_cast<CombatEvents::BeforeDamageOrHealingDeltArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster && !args->handled)
		{
			this->onBeforeDamageTaken(args->damageOrHealing, &args->handled);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageOrHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::BeforeDamageOrHealingTakenArgs* args = static_cast<CombatEvents::BeforeDamageOrHealingTakenArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->handled)
		{
			this->onBeforeDamageTaken(args->damageOrHealing, &args->handled);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityTimelineReset, [=](EventCustom* eventCustom)
	{
		CombatEvents::TimelineResetArgs* args = static_cast<CombatEvents::TimelineResetArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target)
		{
			this->onTimelineReset(args->wasInterrupt);
		}
	}));
}

void Buff::registerHackables()
{
}

void Buff::onTimelineReset(bool wasInterrupt)
{
}

void Buff::onBeforeDamageTaken(int* damageOrHealing, bool* handled)
{
}

void Buff::onBeforeDamageDelt(int* damageOrHealing, bool* handled)
{
}

void Buff::unregisterHackables()
{
	if (this->target == nullptr)
	{
		return;
	}

	for (auto it = this->hackables.begin(); it != this->hackables.end(); it++)
	{
		this->target->unregisterCode(*it);
	}
}

void Buff::removeBuff()
{
	if (this->getParent() != nullptr)
	{
		// unregisterHackables will be indirectly called due to the onExit trigger
		this->getParent()->removeChild(this);
	}
}
