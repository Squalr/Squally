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
#include "Scenes/Platformer/Inventory/Items/Consumables/Consumable.h"
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

CombatAIHelper::~CombatAIHelper()
{
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

void CombatAIHelper::initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities)
{
	this->playerEntities = playerEntities;
	this->enemyEntities = enemyEntities;
}

void CombatAIHelper::performRetargetCorrections(TimelineEntry* attackingEntry)
{
	if (attackingEntry == nullptr)
	{
		return;
	}

	this->selectedTarget = attackingEntry->getStagedTarget();
	this->selectedAttack = attackingEntry->getStagedCast();

	if (this->selectedTarget == nullptr || this->selectedAttack == nullptr)
	{
		return;
	}

	// Clear target entity if invalid
	switch(this->selectedAttack->getAttackType())
	{
		case PlatformerAttack::AttackType::Resurrection:
		{
			if (this->selectedTarget->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->selectedTarget = nullptr;
			}
			break;
		}
		case PlatformerAttack::AttackType::Damage:
		case PlatformerAttack::AttackType::Debuff:
		case PlatformerAttack::AttackType::Buff:
		case PlatformerAttack::AttackType::Healing:
		{
			if (!this->selectedTarget->getStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
			{
				this->selectedTarget = nullptr;
			}
			break;
		}
		default:
		{
			break;
		}
	}

	if (this->selectedTarget != nullptr)
	{
		return;
	}
	
	// Use AI to auto-choose attack and entity. Start by just trying to re-target.
	this->selectTarget(attackingEntry);
	
	attackingEntry->stageTarget(this->selectedTarget);

	if (this->selectedTarget != nullptr)
	{
		return;
	}
	
	// Retarget failed. We'll just have to pick an attack/target at random then.
	this->selectAttack(attackingEntry);
	this->selectTarget(attackingEntry);

	attackingEntry->stageCast(this->selectedAttack);
	attackingEntry->stageTarget(this->selectedTarget);
}

void CombatAIHelper::performAIActions(TimelineEntry* attackingEntry)
{
	this->selectedTarget = nullptr;
	this->selectedAttack = nullptr;

	attackingEntry->stageCast(nullptr);
	attackingEntry->stageTarget(nullptr);

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

void CombatAIHelper::selectAttack(TimelineEntry* attackingEntry)
{
	PlatformerEntity* attackingEntity = attackingEntry == nullptr ? nullptr : attackingEntry->getEntity();
	EntityAttackBehavior* attackBehavior = attackingEntity == nullptr ? nullptr : attackingEntity->getAttachedBehavior<EntityAttackBehavior>();

	if (attackingEntry == nullptr || attackingEntity == nullptr || attackBehavior == nullptr)
	{
		return;
	}

	std::vector<PlatformerAttack*> attackList = attackingEntry->isPlayerEntry() ? attackBehavior->getNoCostAttacks() : attackBehavior->getAvailableAttacks();
	std::vector<Consumable*> consumablesList = attackingEntry->isPlayerEntry() ? std::vector<Consumable*>() : attackBehavior->getAvailableConsumables();
	
	for (auto next : consumablesList)
	{
		attackList.push_back(next->getAssociatedAttack(attackingEntity));
	}

	const std::vector<PlatformerEntity*>& sameTeam = attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;
	const std::vector<PlatformerEntity*>& otherTeam = !attackingEntry->isPlayerEntry() ? this->playerEntities : this->enemyEntities;

	// Filter usable attacks
	attackList.erase(std::remove_if(attackList.begin(), attackList.end(),
		[=](PlatformerAttack* next)
	{
		return !next->isWorthUsing(sameTeam, otherTeam);
	}), attackList.end());

	// Prioritize resurrection > healing > damage
	this->trySelectResurrectionSkill(attackingEntry, attackList);
	this->trySelectHealingSkill(attackingEntry, attackList);
	this->trySelectDamageSkill(attackingEntry, attackList);
}

void CombatAIHelper::trySelectResurrectionSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList)
{
	if (this->selectedAttack != nullptr)
	{
		return;
	}

	// TODO: Move this logic into isWorthUsing when resurrection skill added
	/*
	bool hasDeadAlly = false;

	for (auto entity : sameTeam)
	{
		int health = entity->getStateOrDefaultInt(StateKeys::Health, 0);
		int maxHealth = entity->getStateOrDefaultInt(StateKeys::MaxHealth, 0);
		bool isAlive = entity->getStateOrDefaultBool(StateKeys::IsAlive, true);

		if (!isAlive)
		{
			hasDeadAlly = true;
		}
	}

	if (!hasDeadAlly || attackProbabilities.probabilities.empty())
	{
		return;
	}
	*/

	ProbabilityMap attackProbabilities = this->buildCumulativeProbabilityMap(attackList, [=](PlatformerAttack* attack)
	{
		return attack->getAttackType() == PlatformerAttack::AttackType::Resurrection;
	});

	this->selectedAttack = attackProbabilities.getRandomAttack();
}

void CombatAIHelper::trySelectHealingSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList)
{
	if (this->selectedAttack != nullptr)
	{
		return;
	}

	ProbabilityMap attackProbabilities = this->buildCumulativeProbabilityMap(attackList, [=](PlatformerAttack* attack)
	{
		return attack->getAttackType() == PlatformerAttack::AttackType::Healing;
	});

	this->selectedAttack = attackProbabilities.getRandomAttack();
}

void CombatAIHelper::trySelectDamageSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList)
{
	if (this->selectedAttack != nullptr)
	{
		return;
	}

	ProbabilityMap attackProbabilities = this->buildCumulativeProbabilityMap(attackList, [=](PlatformerAttack* attack)
	{
		return attack->getAttackType() == PlatformerAttack::AttackType::Damage || attack->getAttackType() == PlatformerAttack::AttackType::Debuff;
	});

	this->selectedAttack = attackProbabilities.getRandomAttack();
}

CombatAIHelper::ProbabilityMap CombatAIHelper::buildCumulativeProbabilityMap(const std::vector<PlatformerAttack*>& attackList, std::function<bool(PlatformerAttack*)> predicate)
{
	std::vector<AttackProbability> probabilities = std::vector<AttackProbability>();
	float cumulativeProbability = 0.0f;

	for (auto attack : attackList)
	{
		// Only build an attack probability map for attacks that match the given predicate
		if (predicate(attack))
		{
			cumulativeProbability += attack->getPriority();
			probabilities.push_back(AttackProbability(attack, cumulativeProbability));
		}
	}

	return ProbabilityMap(probabilities, cumulativeProbability);
}
