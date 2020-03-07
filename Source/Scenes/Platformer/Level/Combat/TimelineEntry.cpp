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
#include "Objects/Camera/CameraFocus.h"
#include "Objects/Platformer/Camera/CameraTarget.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/Buffs/Defend/Defend.h"
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorBase.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float TimelineEntry::CastPercentage = 0.75f;
const float TimelineEntry::BaseSpeedMultiplier = 0.175f;

TimelineEntry* TimelineEntry::create(PlatformerEntity* entity, int spawnIndex)
{
	TimelineEntry* instance = new TimelineEntry(entity, spawnIndex);

	instance->autorelease();

	return instance;
}

TimelineEntry::TimelineEntry(PlatformerEntity* entity, int spawnIndex) : super()
{
	this->entity = entity;
	this->line = Sprite::create(UIResources::Combat_Line);
	this->circle = this->isPlayerEntry() ? Sprite::create(UIResources::Combat_PlayerCircle) : Sprite::create(UIResources::Combat_EnemyCircle);
	this->emblem = Sprite::create(entity == nullptr ? UIResources::EmptyImage : entity->getEmblemResource());
	this->skull = Sprite::create(UIResources::Combat_Skull);
	this->orphanedAttackCache = Node::create();
	this->isCasting = false;
	this->spawnIndex = spawnIndex;
	this->combatBehavior = nullptr;

	this->interruptBonus = 0.0f;
	this->progress = 0.0f;

	this->addChild(this->line);
	this->addChild(this->circle);
	this->addChild(this->emblem);
	this->addChild(this->skull);
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
	this->skull->setVisible(false);

	if (this->entity != nullptr)
	{
		this->entity->watchForAttachedBehavior<EntityCombatBehaviorBase>([=](EntityCombatBehaviorBase* combatBehavior)
		{
			this->combatBehavior = combatBehavior;
		});
	}

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCastBlocked, [=](EventCustom* eventCustom)
	{
		CombatEvents::CastBlockedArgs* args = static_cast<CombatEvents::CastBlockedArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target == this->entity)
		{
			this->isBlocking = true;
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventDamage, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			if (this->getEntity()->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyDamage(args->caster, args->damageOrHealing);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventHealing, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			if (this->getEntity()->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyHealing(args->caster, args->damageOrHealing);
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

	if (this->getEntity() == nullptr)
	{
		return;
	}

	if (this->getEntity()->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
	{
		this->emblem->setVisible(true);
		this->skull->setVisible(false);
	}
	else
	{
		this->emblem->setVisible(false);
		this->skull->setVisible(true);
	}
}

PlatformerEntity* TimelineEntry::getEntity()
{
	return this->entity;
}

void TimelineEntry::applyDamage(PlatformerEntity* caster, int damage)
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	// Store the sign. Buff modifiers assume positive numbers, however hacking can cause positive damage (healing)
	int sign = damage < 0 ? -1 : 1;
	
	damage = std::abs(damage);

	// Modify outgoing damage
	CombatEvents::TriggerEntityStatsModifyDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage));
	CombatEvents::TriggerEntityBuffsModifyDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage));

	// Modify incoming damage
	CombatEvents::TriggerEntityStatsModifyDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage));
	CombatEvents::TriggerEntityBuffsModifyDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage));

	this->tryInterrupt();

	int health = this->getEntity()->getStateOrDefaultInt(StateKeys::Health, 0);

	this->getEntity()->setState(StateKeys::Health, Value(health + damage * sign));

	CombatEvents::TriggerDamageDelt(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), damage));
}

void TimelineEntry::applyHealing(PlatformerEntity* caster, int healing)
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	// Store the sign. Buff modifiers assume positive numbers, however hacking can cause negative healing (damage)
	int sign = healing < 0 ? -1 : 1;

	healing = std::abs(healing);

	// Modify outgoing healing
	CombatEvents::TriggerEntityStatsModifyHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing));
	CombatEvents::TriggerEntityBuffsModifyHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing));

	// Modify incoming healing
	CombatEvents::TriggerEntityStatsModifyHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing));
	CombatEvents::TriggerEntityBuffsModifyHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing));

	int health = this->getEntity()->getStateOrDefaultInt(StateKeys::Health, 0);

	this->getEntity()->setState(StateKeys::Health, Value(health + healing * sign));

	CombatEvents::TriggerHealingDelt(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), healing));
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
	float speed = this->combatBehavior == nullptr ? 1.0f : this->combatBehavior->getTimelineSpeed();

	this->progress += (dt * (speed + this->interruptBonus) * TimelineEntry::BaseSpeedMultiplier);
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

		ObjectEvents::QueryObjects<CameraFocus>(QueryObjectsArgs<CameraFocus>([&](CameraFocus* cameraTarget)
		{
			GameCamera::getInstance()->setTarget(cameraTarget->getTrackingData());
		}), CameraFocus::MapKeyCameraFocus);
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

	this->cameraFocusEntry();

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
					this->target->cameraFocusEntry();
				},
				[=]()
				{
					this->resetTimeline();
					CombatEvents::TriggerResumeTimeline();
				}
			);
		}),
		nullptr
	));
}

void TimelineEntry::cameraFocusEntry()
{
	std::string cameraTag = (this->isPlayerEntry() ? "player" : "enemy") + ("-camera-" + std::to_string(this->spawnIndex));

	ObjectEvents::QueryObjects<CameraTarget>(QueryObjectsArgs<CameraTarget>([&](CameraTarget* cameraTarget)
	{
		GameCamera::getInstance()->setTarget(cameraTarget->getTrackingData());
	}), cameraTag);
}

void TimelineEntry::tryInterrupt()
{
	if (!this->isBlocking && !this->isCasting)
	{
		return;
	}
	
	if (this->isBlocking)
	{
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
	this->isBlocking = false;

	CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), true));
}

void TimelineEntry::resetTimeline()
{
	this->progress = std::fmod(this->progress, 1.0f);
	this->interruptBonus = 0.0f;
	this->isCasting = false;
	this->isBlocking = false;

	CombatEvents::TriggerEntityTimelineReset(CombatEvents::TimelineResetArgs(this->getEntity(), false));
}

bool TimelineEntry::isPlayerEntry()
{
	return (dynamic_cast<PlatformerEnemy*>(this->entity) == nullptr);
}
