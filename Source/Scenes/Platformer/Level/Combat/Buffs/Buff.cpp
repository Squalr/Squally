#include "Buff.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/CombatEvents.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

Buff::Buff(PlatformerEntity* caster, PlatformerEntity* target, std::string buffIconResource, BuffData buffData)
{
	this->caster = caster;
	this->owner = target;
	this->buffData = buffData;
	this->iconContainer = Node::create();
	this->buffGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->buffIcon = Sprite::create(buffIconResource);
	this->hackables = std::vector<HackableCode*>();
	this->elapsedTime = 0.0f;
	this->wasRemoved = false;
	this->isBuffIconPresent = !buffIconResource.empty();

	this->iconContainer->setVisible(this->isBuffIconPresent);

	this->iconContainer->addChild(this->buffGlow);
	this->iconContainer->addChild(this->buffIcon);
	this->addChild(this->iconContainer);
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

void Buff::initializePositions()
{
	super::initializePositions();
	
	this->iconContainer->setPositionY(this->owner->getEntitySize().height / 2.0f + 32.0f);
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

		if (args != nullptr && args->target == this->owner && !args->isHandled())
		{
			this->onModifyTimelineSpeed(args->speed, [=](){ args->handle(); });
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->owner && !args->isHandled())
		{
			this->onBeforeDamageDelt(ModifyableDamageOrHealing(
				args->damageOrHealing,
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				AbilityType::Physical,
				args->caster,
				args->target,
				[=](){ args->handle(); }
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityModifyDamageDeltComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster)
		{
			this->onAfterDamageDelt(DamageOrHealing(
				args->damageOrHealing,
				args->damageOrHealing,
				args->damageOrHealing,
				AbilityType::Physical,
				args->caster,
				args->target
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->owner && !args->isHandled())
		{
			this->onBeforeDamageTaken(ModifyableDamageOrHealing(
				args->damageOrHealing,
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				AbilityType::Physical,
				args->caster,
				args->target,
				[=](){ args->handle(); }
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityModifyDamageTakenComplete, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->owner)
		{
			this->onAfterDamageTaken(DamageOrHealing(
				args->damageOrHealing,
				args->damageOrHealing,
				args->damageOrHealing,
				AbilityType::Physical,
				args->caster,
				args->target
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster && !args->isHandled())
		{
			this->onBeforeHealingDelt(ModifyableDamageOrHealing(
				args->damageOrHealing,
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				AbilityType::Physical,
				args->caster,
				args->target,
				[=](){ args->handle(); }
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->owner && !args->isHandled())
		{
			this->onBeforeHealingTaken(ModifyableDamageOrHealing(
				args->damageOrHealing,
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				*(args->damageOrHealing),
				AbilityType::Physical,
				args->caster,
				args->target,
				[=](){ args->handle(); }
			));
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityTimelineReset, [=](EventCustom* eventCustom)
	{
		CombatEvents::TimelineResetArgs* args = static_cast<CombatEvents::TimelineResetArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->owner)
		{
			this->onTimelineReset(args->wasInterrupt);
		}
	}));
}

void Buff::registerHackables()
{
}

bool Buff::hasBuffIcon()
{
	return this->isBuffIconPresent;
}

void Buff::setBuffIndex(int index, int maxIndex)
{
	const float BuffSpacing = 64.0f;

	this->iconContainer->setPositionX(-float(maxIndex) * BuffSpacing / 2.0f + float(index) * BuffSpacing);
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

float Buff::getRemainingDuration()
{
	return MathUtils::clamp(this->buffData.duration - this->elapsedTime, 0.0f, this->buffData.duration);
}

void Buff::onModifyTimelineSpeed(float* timelineSpeed, std::function<void()> handleCallback)
{
}

void Buff::onTimelineReset(bool wasInterrupt)
{
}

void Buff::onBeforeDamageTaken(ModifyableDamageOrHealing damageOrHealing)
{
}

void Buff::onBeforeDamageDelt(ModifyableDamageOrHealing damageOrHealing)
{
}

void Buff::onAfterDamageTaken(DamageOrHealing damageOrHealing)
{
}

void Buff::onAfterDamageDelt(DamageOrHealing damageOrHealing)
{
}

void Buff::onBeforeHealingTaken(ModifyableDamageOrHealing damageOrHealing)
{
}

void Buff::onBeforeHealingDelt(ModifyableDamageOrHealing damageOrHealing)
{
}

void Buff::unregisterHackables()
{
	if (this->owner == nullptr)
	{
		return;
	}

	for (auto next : this->hackables)
	{
		this->owner->unregisterCode(next);
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
	if (this->wasRemoved)
	{
		return;
	}
	
	this->wasRemoved = true;
	
	CombatEvents::TriggerBuffRemoved(CombatEvents::BuffRemovedArgs(this->owner, this));

	if (this->removeBuffCallback != nullptr)
	{
		this->removeBuffCallback();
	}
}

void Buff::registerClippyOnto(std::string identifier, std::function<Clippy*()> clippyFunc)
{
	if (this->owner == nullptr)
	{
		return;
	}
	
	this->owner->registerClippyOnto(identifier, clippyFunc);
}
