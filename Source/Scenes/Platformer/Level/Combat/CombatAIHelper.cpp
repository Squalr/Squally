#include "CombatAIHelper.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

CombatAIHelper* CombatAIHelper::create()
{
	CombatAIHelper* instance = new CombatAIHelper();

	instance->autorelease();

	return instance;
}

CombatAIHelper::CombatAIHelper()
{
	this->selectedTarget = nullptr;
	this->selectedAttack = nullptr;
}

void CombatAIHelper::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void CombatAIHelper::initializePositions()
{
	super::initializePositions();
}

void CombatAIHelper::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventRequestAIAction, [=](EventCustom* eventCustom)
	{
		CombatEvents::AIRequestArgs* args = static_cast<CombatEvents::AIRequestArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->performAIActions(args->attackingEntry);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventRequestRetargetCorrection, [=](EventCustom* eventCustom)
	{
		CombatEvents::AIRequestArgs* args = static_cast<CombatEvents::AIRequestArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->performRetargetCorrections(args->attackingEntry);
		}
	}));
}

void CombatAIHelper::update(float dt)
{
	super::update(dt);
}

void CombatAIHelper::initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	this->playerEntities = playerEntities;
	this->enemyEntities = enemyEntities;
}

void CombatAIHelper::performRetargetCorrections(TimelineEntry* attackingEntity)
{
	if (attackingEntity == nullptr)
	{
		return;
	}

	this->selectedTarget = attackingEntity->getStagedTarget();
	this->selectedAttack = attackingEntity->getStagedCast();

	if (this->selectedTarget == nullptr || this->selectedAttack == nullptr)
	{
		return;
	}

	if (this->selectedTarget->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool() &&
		this->selectedAttack->getAttackType() != PlatformerAttack::AttackType::Resurrection)
	{
		return;
	}
	
	// Use AI to auto-choose attack and entity. Start by just trying to re-target.
	this->selectTarget(attackingEntity);

	if (this->selectedTarget != nullptr)
	{
		return;
	}
	
	// Retarget failed. We'll just have to pick an attack/target at random then.
	this->selectAttack(attackingEntity);
	this->selectTarget(attackingEntity);
}

void CombatAIHelper::performAIActions(TimelineEntry* attackingEntry)
{
	this->selectedTarget = nullptr;
	this->selectedAttack = nullptr;

	this->selectAttack(attackingEntry);
	this->selectTarget(attackingEntry);

	// Error!
	if (attackingEntry == nullptr || this->selectedTarget == nullptr || this->selectedAttack == nullptr)
	{
		CombatEvents::TriggerResumeTimeline();

		return;
	}

	attackingEntry->stageCast(this->selectedAttack);
	attackingEntry->stageTarget(this->selectedTarget);

	// Choices made, resume timeline
	CombatEvents::TriggerResumeTimeline();
}

void CombatAIHelper::selectAttack(TimelineEntry* attackingEntry)
{
	if (attackingEntry == nullptr)
	{
		return;
	}

	PlatformerEntity* attackingEntity = attackingEntry->getEntity();

	if (attackingEntity == nullptr)
	{
		return;
	}

	// PHASE 1: Check if available heal target / heal spell
	EntityAttackBehavior* attackBehavior = attackingEntity->getAttachedBehavior<EntityAttackBehavior>();

	if (attackBehavior == nullptr)
	{
		return;
	}

	const std::vector<PlatformerEntity*>& sameTeam = attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;
	const std::vector<PlatformerEntity*>& otherTeam = !attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;
	std::vector<PlatformerAttack*> attackList = attackingEntry->isPlayerEntry() ? attackBehavior->getNoCostAttacks() : attackBehavior->getAvailableAttacks();
	std::vector<PlatformerAttack*> consumablesList = attackingEntry->isPlayerEntry()
		? std::vector<PlatformerAttack*>()
		: attackBehavior->getAvailableConsumables();
	bool hasWeakAlly = false;
	bool hasDeadAlly = false;
	float selectedAttackPriority = -1.0f;
	const float WeakPercentage = 0.5f;

	for (auto it = consumablesList.begin(); it != consumablesList.end(); it++)
	{
		attackList.push_back(*it);
	}

	for (auto it = sameTeam.begin(); it != sameTeam.end(); it++)
	{
		int health = (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
		int maxHealth = (*it)->getStateOrDefaultInt(StateKeys::MaxHealth, 0);
		bool isAlive = (*it)->getStateOrDefaultBool(StateKeys::IsAlive, true);

		if (!isAlive)
		{
			hasDeadAlly = true;
		}

		if (isAlive && maxHealth >= 0 && std::round(float(health) / float(maxHealth)) <= WeakPercentage)
		{
			hasWeakAlly = true;
		}
	}
	
	// Prioritize resurrection
	if (!attackingEntry->isPlayerEntry() && hasDeadAlly)
	{
		for (auto it = attackList.begin(); it != attackList.end(); it++)
		{
			switch((*it)->getAttackType())
			{
				case PlatformerAttack::AttackType::Resurrection:
				{
					if ((*it)->getPriority() > selectedAttackPriority)
					{
						this->selectedAttack = *it;
					}
				}
				default:
				{
					break;
				}
			}
		}
	}

	if (this->selectedAttack != nullptr)
	{
		return;
	}

	// Prioritize heals next
	if (!attackingEntry->isPlayerEntry() && hasWeakAlly)
	{
		for (auto it = attackList.begin(); it != attackList.end(); it++)
		{
			switch((*it)->getAttackType())
			{
				case PlatformerAttack::AttackType::Healing:
				{
					if ((*it)->getPriority() > selectedAttackPriority)
					{
						this->selectedAttack = *it;
					}
				}
				default:
				{
					break;
				}
			}
		}
	}

	if (this->selectedAttack != nullptr)
	{
		return;
	}

	// PHASE 2: Just pick the highest priority available attack
	for (auto it = attackList.begin(); it != attackList.end(); it++)
	{
		switch((*it)->getAttackType())
		{
			case PlatformerAttack::AttackType::Damage:
			case PlatformerAttack::AttackType::Debuff:
			{
				if ((*it)->getPriority() > selectedAttackPriority)
				{
					this->selectedAttack = *it;
				}
			}
			default:
			{
				break;
			}
		}
	}
}

void CombatAIHelper::selectTarget(TimelineEntry* attackingEntry)
{
	if (attackingEntry == nullptr || this->selectedAttack == nullptr)
	{
		return;
	}

	const std::vector<PlatformerEntity*>& sameTeam = attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;
	const std::vector<PlatformerEntity*>& otherTeam = !attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;

	PlatformerEntity* target = nullptr;
	
	switch(this->selectedAttack->getAttackType())
	{
		case PlatformerAttack::AttackType::Buff:
		{
			target = attackingEntry->getEntity();

			break;
		}
		case PlatformerAttack::AttackType::Healing:
		{
			// Currently just picking the highest health target. This is a user-friendly AI strategy.
			for (auto it = sameTeam.begin(); it != sameTeam.end(); it++)
			{
				bool isAlive = (*it) == nullptr ? false : (*it)->getStateOrDefaultBool(StateKeys::IsAlive, true);
				int health = (*it) == nullptr ? 0 : (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
				int targetHealth = target == nullptr ? health : target->getStateOrDefaultInt(StateKeys::Health, 0);
				
				if (isAlive && health <= targetHealth)
				{
					target = *it;
				}
			}

			break;
		}
		case PlatformerAttack::AttackType::Resurrection:
		{
			for (auto it = sameTeam.begin(); it != sameTeam.end(); it++)
			{
				bool isAlive = (*it) == nullptr ? false : (*it)->getStateOrDefaultBool(StateKeys::IsAlive, true);
				
				if (!isAlive)
				{
					target = *it;
				}
			}

			break;
		}
		case PlatformerAttack::AttackType::Debuff:
		{
			break;
		}
		case PlatformerAttack::AttackType::Damage:
		default:
		{
			// Currently just picking the highest health target. This is a user-friendly AI strategy.
			for (auto it = otherTeam.begin(); it != otherTeam.end(); it++)
			{
				int health = (*it) == nullptr ? 0 : (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
				int targetHealth = target == nullptr ? 0 : target->getStateOrDefaultInt(StateKeys::Health, 0);
				
				if (health >= targetHealth)
				{
					target = *it;
				}
			}

			break;
		}
	}

	this->selectedTarget = target;
}
