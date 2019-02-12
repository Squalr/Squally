#include "EnemyAIHelper.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/ObjectEvents.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Maps/Platformer/Combat/Attacks/PlatformerAttack.h"
#include "Scenes/Maps/Platformer/Combat/TimelineEntry.h"

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
	PlatformerEntity* target = this->selectTarget(attackingEntity);
	PlatformerAttack* attack = this->selectAttack(attackingEntity);

	// Error!
	if (attackingEntity == nullptr || target == nullptr || attack == nullptr)
	{
		CombatEvents::TriggerResumeTimeline();

		return;
	}

	attackingEntity->stageCast(attack);
	attackingEntity->stageTarget(target);

	CombatEvents::TriggerResumeTimeline();
}

PlatformerAttack* EnemyAIHelper::selectAttack(TimelineEntry* attackingEntry)
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

	PlatformerAttack* attack = nullptr;

	std::vector<PlatformerAttack*> attackList = attackingEntity->getAttacks();

	// TODO: Something intelligent for selecting attacks
	// Probably:
	// - Check if there is an available heal spell and a weak (< x%) ally
	// - Check if enough mana for a big attack (probability based)
	// - Otherwise just hit em' with a basic attack
	for (auto it = attackList.begin(); it != attackList.end(); it++)
	{
		attack = *it;
	}

	return attack;
}

PlatformerEntity* EnemyAIHelper::selectTarget(TimelineEntry* attackingEntry)
{
	if (attackingEntry == nullptr)
	{
		return nullptr;
	}

	PlatformerEntity* target = nullptr;
	std::vector<PlatformerEntity*> playerEntities = std::vector<PlatformerEntity*>();

	ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEntity>([&](PlatformerEntity* entity)
	{
		if (dynamic_cast<PlatformerEnemy*>(entity) != nullptr)
		{
			return;
		}

		playerEntities.push_back(entity);
	}));

	// Currently just picking the highest health target. This is a user-friendly AI strategy.
	for (auto it = playerEntities.begin(); it != playerEntities.end(); it++)
	{
		if (target == nullptr)
		{
			target = *it;
		}
		else
		{
			if ((*it)->getHealth() > target->getHealth())
			{
				target = *it;
			}
		}
	}

	return target;
}
