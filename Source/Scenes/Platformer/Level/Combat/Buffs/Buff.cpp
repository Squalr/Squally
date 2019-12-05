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
	this->showClippy = false;
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
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

		if (args != nullptr && args->caster == this->caster && !args->isHandled())
		{
			this->onBeforeDamageDelt(args->damageOrHealing, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageOrHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::BeforeDamageOrHealingTakenArgs* args = static_cast<CombatEvents::BeforeDamageOrHealingTakenArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onBeforeDamageTaken(args->damageOrHealing, args->blocked, [=](){ args->handle(); });
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

void Buff::enableClippy()
{
	this->showClippy = true;
}

void Buff::disableClippy()
{
	this->showClippy = false;
}

void Buff::registerHackables()
{
}

void Buff::onTimelineReset(bool wasInterrupt)
{
}

void Buff::onBeforeDamageTaken(int* damageOrHealing, bool* blocked, std::function<void()> handleCallback)
{
}

void Buff::onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback)
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
