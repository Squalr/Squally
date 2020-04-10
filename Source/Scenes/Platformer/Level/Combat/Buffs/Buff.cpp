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
	this->target = target;
	this->buffData = buffData;
	this->iconContainer = Node::create();
	this->buffGlow = Sprite::create(UIResources::HUD_EmblemGlow);
	this->buffIcon = Sprite::create(buffIconResource);
	this->hackables = std::vector<HackableCode*>();
	this->elapsedTime = 0.0f;
	this->wasRemoved = false;
	this->isBuffIconPresent = !buffIconResource.empty();

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
	
	this->iconContainer->setPositionY(this->target->getEntitySize().height / 2.0f + 32.0f);
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
			this->onBeforeDamageDelt(args->damageOrHealing, [=](){ args->handle(); }, args->caster, args->target);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyDamageTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onBeforeDamageTaken(args->damageOrHealing, [=](){ args->handle(); }, args->caster, args->target);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingDelt, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->caster == this->caster && !args->isHandled())
		{
			this->onBeforeHealingDelt(args->damageOrHealing, [=](){ args->handle(); }, args->caster, args->target);
		}
	}));

	this->addEventListener(EventListenerCustom::create(CombatEvents::EventEntityBuffsModifyHealingTaken, [=](EventCustom* eventCustom)
	{
		CombatEvents::ModifiableDamageOrHealingArgs* args = static_cast<CombatEvents::ModifiableDamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->target && !args->isHandled())
		{
			this->onBeforeHealingTaken(args->damageOrHealing, [=](){ args->handle(); }, args->caster, args->target);
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

void Buff::onBeforeDamageTaken(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
}

void Buff::onBeforeDamageDelt(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
}

void Buff::onBeforeHealingTaken(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
{
}

void Buff::onBeforeHealingDelt(int* damageOrHealing, std::function<void()> handleCallback, PlatformerEntity* caster, PlatformerEntity* target)
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
	if (this->wasRemoved)
	{
		return;
	}
	
	this->wasRemoved = true;
	
	CombatEvents::TriggerBuffRemoved(CombatEvents::BuffRemovedArgs(this->target, this));

	if (this->removeBuffCallback != nullptr)
	{
		this->removeBuffCallback();
	}
}
