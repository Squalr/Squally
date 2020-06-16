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
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
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
	this->circleSelected = this->isPlayerEntry() ? Sprite::create(UIResources::Combat_PlayerCircleSelected) : Sprite::create(UIResources::Combat_EnemyCircleSelected);
	this->emblem = Sprite::create(entity == nullptr ? UIResources::EmptyImage : entity->getEmblemResource());
	this->overlayCircle = Sprite::create(UIResources::Combat_OverlayCircle);
	this->skull = Sprite::create(UIResources::Combat_Skull);
	this->targetIcons = std::vector<cocos2d::Sprite*>();
	this->orphanedAttackCache = Node::create();
	this->isCasting = false;
	this->isBlocking = false;
	this->spawnIndex = spawnIndex;
	this->combatBehavior = nullptr;
	
	for (int index = 0; index < 5; index++)
	{
		Sprite* target = Sprite::create(UIResources::Menus_Icons_CrossHair);

		target->setVisible(false);

		this->targetIcons.push_back(target);
	}

	this->interruptBonus = 0.0f;
	this->progress = 0.0f;
	this->circleSelected->setVisible(false);

	this->addChild(this->line);
	this->addChild(this->circle);
	this->addChild(this->circleSelected);
	this->addChild(this->emblem);
	this->addChild(this->overlayCircle);
	this->addChild(this->skull);

	for (auto next : this->targetIcons)
	{
		this->addChild(next);
	}

	this->addChild(this->orphanedAttackCache);
}

TimelineEntry::~TimelineEntry()
{
}

void TimelineEntry::onEnter()
{
	super::onEnter();

	this->currentCast = nullptr;
	this->targets = std::vector<PlatformerEntity*>();
	this->targetsAsEntries = std::vector<TimelineEntry*>();
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
			if (this->getEntity()->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyDamage(args->caster, args->damageOrHealing, args->disableBuffProcessing, args->abilityType);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventHealing, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			if (this->getEntity()->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyHealing(args->caster, args->damageOrHealing, args->disableBuffProcessing, args->abilityType);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventManaRestore, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			if (this->getEntity()->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyManaRestore(args->caster, args->damageOrHealing, args->disableBuffProcessing, args->abilityType);
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventManaDrain, [=](EventCustom* eventCustom)
	{
		CombatEvents::DamageOrHealingArgs* args = static_cast<CombatEvents::DamageOrHealingArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->target != nullptr && args->target == this->getEntity())
		{
			if (this->getEntity()->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->applyManaDrain(args->caster, args->damageOrHealing, args->disableBuffProcessing, args->abilityType);
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

	if (this->getEntity()->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
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

void TimelineEntry::applyDamage(PlatformerEntity* caster, int damage, bool disableBuffProcessing, AbilityType abilityType)
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	if (!disableBuffProcessing)
	{
		// Apply stats
		CombatEvents::TriggerEntityStatsModifyDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage, abilityType));
		CombatEvents::TriggerEntityStatsModifyDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage, abilityType));

		// Modify outgoing damage
		CombatEvents::TriggerEntityBuffsModifyDamageDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage, abilityType));
		CombatEvents::TriggerEntityDamageDeltModifyComplete(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), damage, abilityType));

		// Modify incoming damage
		CombatEvents::TriggerEntityBuffsModifyDamageTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &damage, abilityType));
		CombatEvents::TriggerEntityDamageTakenModifyComplete(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), damage, abilityType));
	}

	if (abilityType != AbilityType::Passive)
	{
		this->tryInterrupt();
	}

	int health = this->getEntity()->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);

	this->getEntity()->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(health - damage);
	});

	CombatEvents::TriggerDamageDelt(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), damage, abilityType));
}

void TimelineEntry::applyHealing(PlatformerEntity* caster, int healing, bool disableBuffProcessing, AbilityType abilityType)
{
	if (this->getEntity() == nullptr)
	{
		return;
	}

	if (!disableBuffProcessing)
	{
		// Modify outgoing healing
		CombatEvents::TriggerEntityStatsModifyHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing, abilityType));
		CombatEvents::TriggerEntityBuffsModifyHealingDelt(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing, abilityType));

		// Modify incoming healing
		CombatEvents::TriggerEntityStatsModifyHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing, abilityType));
		CombatEvents::TriggerEntityBuffsModifyHealingTaken(CombatEvents::ModifiableDamageOrHealingArgs(caster, this->getEntity(), &healing, abilityType));
	}

	int health = this->getEntity()->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);

	this->getEntity()->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
	{
		healthBehavior->setHealth(health + healing);
	});

	CombatEvents::TriggerHealingDelt(CombatEvents::DamageOrHealingArgs(caster, this->getEntity(), healing, abilityType));
}

void TimelineEntry::applyManaRestore(PlatformerEntity* caster, int manaGain, bool disableBuffProcessing, AbilityType abilityType)
{
	int mana = this->getEntity()->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0);

	this->getEntity()->getAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(mana + manaGain);
	});

	CombatEvents::TriggerManaRestoreDelt(CombatEvents::ManaRestoreOrDrainArgs(caster, this->getEntity(), manaGain, abilityType));
}

void TimelineEntry::applyManaDrain(PlatformerEntity* caster, int manaGain, bool disableBuffProcessing, AbilityType abilityType)
{
	int mana = this->getEntity()->getRuntimeStateOrDefaultInt(StateKeys::Mana, 0);

	this->getEntity()->getAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
	{
		manaBehavior->setMana(mana + manaGain);
	});

	CombatEvents::TriggerManaDrainDelt(CombatEvents::ManaRestoreOrDrainArgs(caster, this->getEntity(), manaGain, abilityType));
}

void TimelineEntry::stageTargets(std::vector<PlatformerEntity*> targets)
{
	this->targets.clear();

	for (auto next : targets)
	{
		if (next == nullptr)
		{
			continue;
		}

		CombatEvents::TriggerGetAssociatedTimelineEntry(CombatEvents::AssociatedEntryArgs(next, [=](TimelineEntry* timelineEntry)
		{
			this->targets.push_back(next);
			this->targetsAsEntries.push_back(timelineEntry);
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

std::vector<PlatformerEntity*> TimelineEntry::getStagedTargets()
{
	return this->targets;
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
	
	CombatEvents::TriggerEntityBuffsModifyTimelineSpeed(CombatEvents::ModifiableTimelineSpeedArgs(this->getEntity(), &speed));

	this->setProgress(this->progress + (dt * (speed + this->interruptBonus) * TimelineEntry::BaseSpeedMultiplier));
}

void TimelineEntry::addTime(float dt)
{
	this->addTimeWithoutActions(dt);
	this->tryPerformActions();
}

void TimelineEntry::tryPerformActions()
{
	// Cast started
	if (this->progress >= TimelineEntry::CastPercentage && !this->isCasting)
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
		}), CameraFocus::MapKey);
	}
	// Progress complete, do the cast
	else if (this->progress >= 1.0f)
	{
		CombatEvents::TriggerInterruptTimeline();

		if (this->entity != nullptr && this->currentCast != nullptr && !this->targets.empty())
		{
			CombatEvents::TriggerPauseTimeline();

			this->performCast();
		}
		else
		{
			this->resetTimeline();
		}
	}
	else if (this->progress < TimelineEntry::CastPercentage)
	{
		// This is necessary if the entity drifts backwards due to a debuff (thus casting is canceled)
		this->isCasting = false;
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
			if (this->targets.empty())
			{
				this->resetTimeline();
				return;
			}

			this->entity->getAnimations()->clearAnimationPriority();
			this->entity->getAnimations()->playAnimation(this->currentCast->getAttackAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(1.0f, 0.5f, true));
			this->isCasting = false;

			this->currentCast->execute(
				this->entity,
				this->targets,
				[=]()
				{
					// Attack complete -- camera focus target
					if (!this->targetsAsEntries.empty())
					{
						this->targetsAsEntries[0]->cameraFocusEntry();
					}
				},
				[=]()
				{
					this->stageCast(nullptr);
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
		this->setProgress(this->progress / 2.0f);
		this->interruptBonus = 0.1f;
	}
	else if (this->isCasting)
	{
		CombatEvents::TriggerCastInterrupt(CombatEvents::CastInterruptArgs(this->entity));

		this->setProgress(this->progress / 4.0f);
		this->interruptBonus = 0.1f;
	}
	
	this->stageCast(nullptr);
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

void TimelineEntry::setSelected(bool isSelected)
{
	this->circle->setVisible(!isSelected);
	this->circleSelected->setVisible(isSelected);
}

void TimelineEntry::clearBuffTargets()
{
	this->overlayCircle->setOpacity(0);

	for (auto next : this->targetIcons)
	{
		next->setVisible(false);
	}
}

void TimelineEntry::addBuffTarget(std::string iconResource)
{
	this->overlayCircle->setOpacity(128);

	for (auto next : this->targetIcons)
	{
		if (!next->isVisible())
		{
			next->initWithFile(iconResource);
			next->setVisible(true);
			return;
		}
	}
}
