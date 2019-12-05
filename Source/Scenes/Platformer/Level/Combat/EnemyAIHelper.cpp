#include "EnemyAIHelper.h"

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

EnemyAIHelper* EnemyAIHelper::create()
{
	EnemyAIHelper* instance = new EnemyAIHelper();

	instance->autorelease();

	return instance;
}

EnemyAIHelper::EnemyAIHelper()
{
	this->selectedTarget = nullptr;
	this->selectedAttack = nullptr;
}

void EnemyAIHelper::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void EnemyAIHelper::initializePositions()
{
	super::initializePositions();
}

void EnemyAIHelper::initializeListeners()
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
}

void EnemyAIHelper::update(float dt)
{
	super::update(dt);
}

void EnemyAIHelper::initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	this->playerEntities = playerEntities;
	this->enemyEntities = enemyEntities;
}

void EnemyAIHelper::performAIActions(TimelineEntry* attackingEntity)
{
	this->selectedTarget = nullptr;
	this->selectedAttack = nullptr;

	this->selectAttack(attackingEntity);
	this->selectTarget(attackingEntity);

	// Error!
	if (attackingEntity == nullptr || this->selectedTarget == nullptr || this->selectedAttack == nullptr)
	{
		CombatEvents::TriggerResumeTimeline();

		return;
	}

	attackingEntity->stageCast(this->selectedAttack);
	attackingEntity->stageTarget(this->selectedTarget);

	// Choices made, resume timeline
	CombatEvents::TriggerResumeTimeline();
}

void EnemyAIHelper::selectAttack(TimelineEntry* attackingEntry)
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

	std::vector<PlatformerAttack*> attackList = attackBehavior->getAvailableAttacks();
	std::vector<PlatformerAttack*> consumablesList = attackBehavior->getAvailableConsumables();
	bool hasWeakAlly = false;
	float selectedAttackPriority = -1.0f;
	const float WeakPercentage = 0.5f;

	for (auto it = consumablesList.begin(); it != consumablesList.end(); it++)
	{
		attackList.push_back(*it);
	}

	for (auto it = this->enemyEntities.begin(); it != this->enemyEntities.end(); it++)
	{
		int health = (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
		int maxHealth = (*it)->getStateOrDefaultInt(StateKeys::MaxHealth, 0);

		if (maxHealth >= 0 && std::round(float(health) / float(maxHealth)) <= WeakPercentage)
		{
			hasWeakAlly = true;
		}
	}

	if (hasWeakAlly)
	{
		for (auto it = attackList.begin(); it != attackList.end(); it++)
		{
			switch((*it)->getAttackType())
			{
				case PlatformerAttack::AttackType::Healing:
				case PlatformerAttack::AttackType::ProjectileHealing:
				case PlatformerAttack::AttackType::ProjectileBuffSpeed:
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
			case PlatformerAttack::AttackType::ProjectileDamage:
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

void EnemyAIHelper::selectTarget(TimelineEntry* attackingEntry)
{
	if (attackingEntry == nullptr || this->selectedAttack == nullptr)
	{
		return;
	}

	PlatformerEntity* target = nullptr;
	
	switch(this->selectedAttack->getAttackType())
	{
		case PlatformerAttack::AttackType::ProjectileBuffSpeed:
		{
			target = attackingEntry->getEntity();

			break;
		}
		case PlatformerAttack::AttackType::Healing:
		case PlatformerAttack::AttackType::ProjectileHealing:
		{
			// Currently just picking the highest health target. This is a user-friendly AI strategy.
			for (auto it = this->enemyEntities.begin(); it != this->enemyEntities.end(); it++)
			{
				if (target == nullptr)
				{
					target = *it;
					continue;
				}

				bool isAlive = (*it) == nullptr ? false : (*it)->getStateOrDefaultBool(StateKeys::IsAlive, true);
				int health = (*it) == nullptr ? 0 : (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
				int targetHealth = target == nullptr ? 0 : target->getStateOrDefaultInt(StateKeys::Health, 0);
				
				if (isAlive && health < targetHealth)
				{
					target = *it;
				}
			}

			break;
		}
		case PlatformerAttack::AttackType::ProjectileDamage:
		case PlatformerAttack::AttackType::Damage:
		default:
		{
			// Currently just picking the highest health target. This is a user-friendly AI strategy.
			for (auto it = this->playerEntities.begin(); it != this->playerEntities.end(); it++)
			{
				if (target == nullptr)
				{
					target = *it;
					continue;
				}

				int health = (*it) == nullptr ? 0 : (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
				int targetHealth = target == nullptr ? 0 : target->getStateOrDefaultInt(StateKeys::Health, 0);
				
				if (health > targetHealth)
				{
					target = *it;
				}
			}

			break;
		}
	}

	this->selectedTarget = target;
}
