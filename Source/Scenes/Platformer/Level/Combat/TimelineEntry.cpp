#include "TimelineEntry.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/Defend.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float TimelineEntry::CastPercentage = 0.75f;
const float TimelineEntry::BaseSpeedMultiplier = 0.175f;

TimelineEntry* TimelineEntry::create(PlatformerEntity* entity)
{
	TimelineEntry* instance = new TimelineEntry(entity);

	instance->autorelease();

	return instance;
}

TimelineEntry::TimelineEntry(PlatformerEntity* entity)
{
	this->entity = entity;
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = this->isPlayerEntry() ? Sprite::create(UIResources::Combat_PlayerCircle) : Sprite::create(UIResources::Combat_EnemyCircle);
	this->emblem = Sprite::create(entity->getEmblemResource());
	this->orphanedAttackCache = Node::create();

	this->speed = 1.0f;
	this->interruptBonus = 0.0f;
	this->progress = 0.0f;

	this->addChild(this->line);
	this->addChild(this->circle);
	this->addChild(this->emblem);
	this->addChild(this->orphanedAttackCache);
}

void TimelineEntry::onEnter()
{
	super::onEnter();

	this->currentCast = nullptr;
	this->target = nullptr;
	this->isCasting = false;
	this->orphanedAttackCache->removeAllChildren();

	this->scheduleUpdate();
}

void TimelineEntry::initializePositions()
{
	super::initializePositions();

	const float EntryOffsetY = 72.0f;
	const float LineOffsetY = 48.0f;

	if (this->isPlayerEntry())
	{
		this->line->setPositionY(-LineOffsetY);
		this->setPositionY(EntryOffsetY);
	}
	else
	{
		this->line->setPositionY(LineOffsetY);
		this->setPositionY(-EntryOffsetY);
	}
}

void TimelineEntry::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDamageOrHealing, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			CombatEvents::TriggerEntityBuffsModifyDamageOrHealingDelt(CombatEvents::BeforeDamageOrHealingDeltArgs(args->caster, this->getEntity(), &args->damageOrHealing));

			this->applyDamageOrHealing(args->caster, args->damageOrHealing);
		}
	}));
}

void TimelineEntry::update(float dt)
{
	super::update(dt);
}

PlatformerEntity* TimelineEntry::getEntity()
{
	return this->entity;
}

void TimelineEntry::applyDamageOrHealing(PlatformerEntity* caster, int damageOrHealing)
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	CombatEvents::TriggerEntityBuffsModifyDamageOrHealingDelt(CombatEvents::BeforeDamageOrHealingDeltArgs(caster, this->getEntity(), &damageOrHealing));
	CombatEvents::TriggerEntityBuffsModifyDamageOrHealingTaken(CombatEvents::BeforeDamageOrHealingTakenArgs(caster, this->getEntity(), &damageOrHealing));

	if (damageOrHealing < 0)
	{
		this->tryInterrupt();
	}

	this->getEntity()->addHealth(damageOrHealing);
	CombatEvents::TriggerDamageOrHealingDelt(CombatEvents::DamageOrHealingDeltArgs(caster, this->getEntity(), damageOrHealing));
}

void TimelineEntry::stageTarget(PlatformerEntity* target)
{
	this->target = target == nullptr ? nullptr : TimelineEntry::getAssociatedTimelineEntry(target);
}

void TimelineEntry::stageCast(PlatformerAttack* attack)
{
	// If this attach was created by the result of an item, it has no parent, and thus we need to keep a reference to it
	if (attack != nullptr && attack->getParent() == nullptr)
	{
		this->orphanedAttackCache->addChild(attack);
	}

	this->currentCast = attack;
}

void TimelineEntry::defend()
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	this->getEntity()->addChild(Defend::create(this->getEntity()));
}

float TimelineEntry::getProgress()
{
	return this->progress;
}

void TimelineEntry::setProgress(float progress)
{
	this->progress = MathUtils::clamp(progress, 0.0f, 1.0f);
}

void TimelineEntry::addTimeWithoutActions(float dt)
{
	this->progress += (dt * (this->speed + this->interruptBonus) * TimelineEntry::BaseSpeedMultiplier);
}

void TimelineEntry::addTime(float dt)
{
	this->addTimeWithoutActions(dt);

	// Cast started
	if (this->progress > TimelineEntry::CastPercentage && !this->isCasting)
	{
		CombatEvents::TriggerInterruptTimeline();

		this->isCasting = true;

		if (this->isPlayerEntry())
		{
			CombatEvents::TriggerPauseTimeline();
			CombatEvents::TriggerMenuStateChange(CombatEvents::MenuStateArgs(CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect, this));
		}
		else
		{
			CombatEvents::TriggerPauseTimeline();
			CombatEvents::TriggerRequestAIAction(CombatEvents::AIRequestArgs(this));
		}
	}
	// Progress complete, do the cast
	else if (this->progress > 1.0f)
	{
		CombatEvents::TriggerInterruptTimeline();

		if (this->entity != nullptr && this->currentCast != nullptr && this->target != nullptr)
		{
			CombatEvents::TriggerPauseTimeline();

			this->performCast();
		}
		else
		{
			this->resetTimeline();
		}
	}
}

void TimelineEntry::performCast()
{
	this->isCasting = false;
	this->entity->getAnimations()->playAnimation(this->currentCast->getAttackAnimation());

	this->currentCast->execute(
		this->entity,
		this->target->entity,
		[=]()
		{
			this->resetTimeline();
			CombatEvents::TriggerResumeTimeline();
		}
	);
}

void TimelineEntry::tryInterrupt()
{
	if (this->isCasting)
	{
		CombatEvents::TriggerCastInterrupt(CombatEvents::CastInterruptArgs(this->entity));
		this->isCasting = false;
		this->progress = this->progress / 3.0f;
		this->interruptBonus = RandomHelper::random_real(0.05f, 0.1f);

		CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), true));
	}
}

void TimelineEntry::resetTimeline()
{
	this->progress = std::fmod(this->progress, 1.0f);
	this->interruptBonus = 0.0f;

	CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), false));
}

bool TimelineEntry::isPlayerEntry()
{
	return (dynamic_cast<PlatformerEnemy*>(this->entity) == nullptr);
}

TimelineEntry* TimelineEntry::getAssociatedTimelineEntry(PlatformerEntity* entity)
{
	TimelineEntry* associatedEntry = nullptr;

	ObjectEvents::QueryObjects(QueryObjectsArgs<TimelineEntry>([&](TimelineEntry* entry, bool* handled)
	{
		if (entry->getEntity() == entity)
		{
			associatedEntry = entry;

			*handled = true;
		}
	}));

	return associatedEntry;
}
