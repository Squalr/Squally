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

void EnemyAIHelper::performAIActions(TimelineEntry* attackingEntity)
{
	std::vector<PlatformerEntity*> playerEntities = std::vector<PlatformerEntity*>();
	std::vector<PlatformerEntity*> enemyEntities = std::vector<PlatformerEntity*>();

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([&](PlatformerEntity* entity)
	{
		if (dynamic_cast<PlatformerFriendly*>(entity) != nullptr)
		{
			playerEntities.push_back(entity);
		}

		if (dynamic_cast<PlatformerEnemy*>(entity) != nullptr)
		{
			enemyEntities.push_back(entity);
		}
	}), PlatformerEntity::PlatformerEntityTag);

	PlatformerEntity* target = this->selectTarget(attackingEntity, playerEntities, enemyEntities);
	PlatformerAttack* attack = this->selectAttack(attackingEntity, playerEntities, enemyEntities);

	// Error!
	if (attackingEntity == nullptr || target == nullptr || attack == nullptr)
	{
		CombatEvents::TriggerResumeTimeline();

		return;
	}

	attackingEntity->stageCast(attack);
	attackingEntity->stageTarget(target);

	// Choices made, resume timeline
	CombatEvents::TriggerResumeTimeline();
}

PlatformerAttack* EnemyAIHelper::selectAttack(TimelineEntry* attackingEntry, std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	if (attackingEntry == nullptr)
	{
		return nullptr;
	}

	PlatformerEntity* attackingEntity = attackingEntry->getEntity();

	if (attackingEntity == nullptr)
	{
		return nullptr;
	}

	// PHASE 1: Check if available heal target / heal spell
	EntityAttackBehavior* attackBehavior = attackingEntity->getAttachedBehavior<EntityAttackBehavior>();

	if (attackBehavior == nullptr)
	{
		return nullptr;
	}

	std::vector<PlatformerAttack*> attackList = attackBehavior->getAvailableAttacks();
	std::vector<PlatformerAttack*> consumablesList = attackBehavior->getAvailableConsumables();
	PlatformerAttack* attack = nullptr;
	bool hasWeakAlly = false;
	float selectedAttackPriority = -1.0f;
	const float WeakPercentage = 0.5f;

	for (auto it = consumablesList.begin(); it != consumablesList.end(); it++)
	{
		attackList.push_back(*it);
	}

	for (auto it = enemyEntities.begin(); it != enemyEntities.end(); it++)
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
						attack = *it;
					}
				}
				default:
				{
					break;
				}
			}
		}
	}

	if (attack != nullptr)
	{
		return attack;
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
					attack = *it;
				}
			}
			default:
			{
				break;
			}
		}
	}

	return attack;
}

PlatformerEntity* EnemyAIHelper::selectTarget(TimelineEntry* attackingEntry, std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	if (attackingEntry == nullptr)
	{
		return nullptr;
	}

	PlatformerEntity* target = nullptr;

	// Currently just picking the highest health target. This is a user-friendly AI strategy.
	for (auto it = playerEntities.begin(); it != playerEntities.end(); it++)
	{
		if (target == nullptr)
		{
			target = *it;
		}
		else
		{
			int health = (*it)->getStateOrDefaultInt(StateKeys::Health, 0);
			int targetHealth = target->getStateOrDefaultInt(StateKeys::Health, 0);
			
			if (health > targetHealth)
			{
				target = *it;
			}
		}
	}

	return target;
}
