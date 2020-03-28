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

	this->shuffleEntities();

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

	PlatformerEntity* caster = attackingEntry->getEntity();
	
	float bestUtility = std::numeric_limits<float>().min();

	for (auto next : otherTeam)
	{
		float utility = this->selectedAttack->getUseUtility(caster, next, sameTeam, otherTeam);

		if (utility > bestUtility)
		{
			this->selectedTarget = next;
		}
	}
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
		return !next->isWorthUsing(attackingEntity, sameTeam, otherTeam);
	}), attackList.end());

	// Prioritize resurrection > healing > damage
	this->trySelectResurrectionSkill(attackingEntry, attackList);
	this->trySelectHealingSkill(attackingEntry, attackList);
	this->trySelectDamageSkill(attackingEntry, attackList);
}

void CombatAIHelper::shuffleEntities()
{
	std::random_device rd1;
	std::mt19937 g1(rd1());

	std::shuffle(this->playerEntities.begin(), this->playerEntities.end(), g1);

	std::random_device rd2;
	std::mt19937 g2(rd2());

	std::shuffle(this->enemyEntities.begin(), this->enemyEntities.end(), g2);
}

void CombatAIHelper::trySelectResurrectionSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList)
{
	if (this->selectedAttack != nullptr)
	{
		return;
	}

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
		return attack->getAttackType() == PlatformerAttack::AttackType::Damage
			|| attack->getAttackType() == PlatformerAttack::AttackType::Debuff
			|| attack->getAttackType() == PlatformerAttack::AttackType::Buff;
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
			switch(attack->getPriority())
			{
				case PlatformerAttack::Priority::Guaranteed:
				{
					cumulativeProbability += 1.0f;
					break;
				}
				case PlatformerAttack::Priority::VeryCommon:
				{
					cumulativeProbability += 0.75f;
					break;
				}
				case PlatformerAttack::Priority::Common:
				{
					cumulativeProbability += 0.5f;
					break;
				}
				case PlatformerAttack::Priority::Reasonable:
				{
					cumulativeProbability += 0.25f;
					break;
				}
				case PlatformerAttack::Priority::Uncommon:
				{
					cumulativeProbability += 0.15f;
					break;
				}
				case PlatformerAttack::Priority::Rare:
				{
					cumulativeProbability += 0.08f;
					break;
				}
			}

			probabilities.push_back(AttackProbability(attack, cumulativeProbability));
		}
	}

	return ProbabilityMap(probabilities, cumulativeProbability);
}
