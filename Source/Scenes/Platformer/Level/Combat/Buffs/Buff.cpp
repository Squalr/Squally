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

Buff::Buff(PlatformerEntity* caster, PlatformerEntity* target, BuffData buffData)
{
	this->caster = caster;
	this->target = target;
	this->buffData = buffData;
	this->hackables = std::vector<HackableCode*>();
	this->elapsedTime = 0.0f;
}

Buff::~Buff()
{
}

void Buff::onEnter()
{
	super::onEnter();

	this->registerHackables();
}

void Buff::onExit()
{
	super::onExit();
	
	this->unregisterHackables();
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

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onModifyTimelineSpeed(args->speed, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster && !args->isHandled())
		{
			this->onBeforeDamageDelt(args->damageOrHealing, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onBeforeDamageTaken(args->damageOrHealing, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster && !args->isHandled())
		{
			this->onBeforeDamageDelt(args->damageOrHealing, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onBeforeDamageTaken(args->damageOrHealing, [=](){ args->handle(); });
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

void Buff::registerClippy(Clippy* clippy)
{
	if (this->target != nullptr)
	{
		this->target->registerClippy(clippy);
	}
}

void Buff::elapse(float dt)
{
	if (this->buffData.duration > 0.0f)
	{
		this->elapsedTime += dt;

		if (this->elapsedTime >= this->buffData.duration)
		{
			this->removeBuff();
		}
	}
}

void Buff::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
}

void Buff::onTimelineReset(bool wasInterrupt)
{
}

void Buff::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback)
{
}

void Buff::onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback)
{
}

void Buff::onBeforeHealingTaken(int* damageOrHealing, std::function<void()> handleCallback)
{
}

void Buff::onBeforeHealingDelt(int* damageOrHealing, std::function<void()> handleCallback)
{
}

void Buff::unregisterHackables()
{
	if (this->target == nullptr)
	{
		return;
	}

	for (auto next : this->hackables)
	{
		this->target->unregisterCode(next);
	}
}

Buff::BuffData Buff::getBuffData()
{
	return this->buffData;
}

void Buff::setRemoveBuffCallback(std::function<void()> removeBuffCallback)
{
	this->removeBuffCallback = removeBuffCallback;
}

void Buff::removeBuff()
{
	if (this->removeBuffCallback != nullptr)
	{
		this->removeBuffCallback();
	}
}
