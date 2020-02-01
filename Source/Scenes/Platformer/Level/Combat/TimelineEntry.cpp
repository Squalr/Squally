#include "TimelineEntry.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/Defend.h"
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"

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

TimelineEntry::TimelineEntry(PlatformerEntity* entity) : super()
{
	this->entity = entity;
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = this->isPlayerEntry() ? Sprite::create(UIResources::Combat_PlayerCircle) : Sprite::create(UIResources::Combat_EnemyCircle);
	this->emblem = Sprite::create(entity->getEmblemResource());
	this->orphanedAttackCache = Node::create();
	this->isCasting = false;

	this->speed = 1.0f;
	this->interruptBonus = 0.0f;
	this->progress = 0.0f;

	this->addChild(this->line);
	this->addChild(this->circle);
	this->addChild(this->emblem);
	this->addChild(this->orphanedAttackCache);
}

TimelineEntry::~TimelineEntry()
{
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
			if (this->getEntity()->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				CombatEvents::TriggerEntityBuffsModifyDamageOrHealingDelt(CombatEvents::BeforeDamageOrHealingDeltArgs(args->caster, this->getEntity(), &args->damageOrHealing));

				this->applyDamageOrHealing(args->caster, args->damageOrHealing);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGetAssociatedTimelineEntry, [=](EventCustom* eventCustom)
	{
		CombatEvents::AssociatedEntryArgs* args = static_cast<CombatEvents::AssociatedEntryArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->entity == this->getEntity())
		{
			args->onLocated(this);
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

	bool blocked = false;

	CombatEvents::TriggerEntityBuffsModifyDamageOrHealingDelt(CombatEvents::BeforeDamageOrHealingDeltArgs(caster, this->getEntity(), &damageOrHealing));
	CombatEvents::TriggerEntityBuffsModifyDamageOrHealingTaken(CombatEvents::BeforeDamageOrHealingTakenArgs(caster, this->getEntity(), &damageOrHealing, &blocked));

	if (damageOrHealing < 0)
	{
		this->tryInterrupt(blocked);
	}

	int health = this->getEntity()->getStateOrDefaultInt(StateKeys::Health, 0);

	this->getEntity()->setState(StateKeys::Health, Value(health + damageOrHealing));

	CombatEvents::TriggerDamageOrHealingDelt(CombatEvents::DamageOrHealingDeltArgs(caster, this->getEntity(), damageOrHealing));
}

void TimelineEntry::stageTarget(PlatformerEntity* target)
{
	this->target = nullptr;

	if (target != nullptr)
	{
		CombatEvents::TriggerGetAssociatedTimelineEntry(CombatEvents::AssociatedEntryArgs(target, [=](TimelineEntry* timelineEntry)
		{
			this->target = timelineEntry;
		}));
	}
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

PlatformerEntity* TimelineEntry::getStagedTarget()
{
	return this->target == nullptr ? nullptr : this->target->getEntity();
}

PlatformerAttack* TimelineEntry::getStagedCast()
{
	return this->currentCast;
}

void TimelineEntry::defend()
{
	if (this->getEntity() == nullptr)
	{
		return;
	}
	
	this->getEntity()->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(Defend::create(this->getEntity()));
	});
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
	this->tryPerformActions();
}

void TimelineEntry::tryPerformActions()
{
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
	CombatEvents::TriggerRequestRetargetCorrection(CombatEvents::AIRequestArgs(this));

	this->cameraFocusEntity(this->entity);

	this->runAction(Sequence::create(
		DelayTime::create(1.0f),
		CallFunc::create([=]()
		{
			this->isCasting = false;
			this->entity->getAnimations()->playAnimation(this->currentCast->getAttackAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 1.0f);

			this->currentCast->execute(
				this->entity,
				this->target->entity,
				[=]()
				{
					// Attack complete -- camera focus target
					GameCamera::getInstance()->popTarget();
					this->cameraFocusEntity(this->target->entity);
				},
				[=]()
				{
					// Recover finished, camera unfocus target
					GameCamera::getInstance()->popTarget();
					
					this->resetTimeline();
					CombatEvents::TriggerResumeTimeline();
				}
			);
		}),
		nullptr
	));
}

void TimelineEntry::cameraFocusEntity(PlatformerEntity* entity)
{
	// TODO: Direct focus is no good, and hard coded offsets do not work particularly well. Maybe bind each entity to a camera hint obj in the map file?
	GameCamera::getInstance()->pushTarget(CameraTrackingData(
		entity,
		Vec2::ZERO,
		CameraTrackingData::DefaultCameraOffset,
		CameraTrackingData::CameraScrollType::Rectangle,
		Vec2(0.015f, 0.015f),
		1.0f // entity->getStateOrDefault(StateKeys::Zoom, Value(1.0f)).asFloat()
	));
}

void TimelineEntry::tryInterrupt(bool blocked)
{
	if (blocked || this->isCasting)
	{	
		if (blocked)
		{
			CombatEvents::TriggerCastBlocked(CombatEvents::CastBlockedArgs(this->entity));

			this->progress = this->progress / 2.0f;
			this->interruptBonus = 0.1f;
		}
		else if (this->isCasting)
		{
			CombatEvents::TriggerCastInterrupt(CombatEvents::CastInterruptArgs(this->entity));

			this->progress = this->progress / 4.0f;
			this->interruptBonus = 0.1f;
		}
		
		this->isCasting = false;

		CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), true));
	}
}

void TimelineEntry::resetTimeline()
{
	this->progress = std::fmod(this->progress, 1.0f);
	this->interruptBonus = 0.0f;
	this->isCasting = false;

	CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), false));
}

bool TimelineEntry::isPlayerEntry()
{
	return (dynamic_cast<PlatformerEnemy*>(this->entity) == nullptr);
}
