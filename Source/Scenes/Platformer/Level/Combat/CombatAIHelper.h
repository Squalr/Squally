#pragma once

#include "cocos/base/ccRandom.h"

#include "Engine/SmartNode.h"

class PlatformerAttack;
class PlatformerEntity;
class TimelineEntry;

class CombatAIHelper : public SmartNode
{
public:
	static CombatAIHelper* create();

	void initializeEntities(std::vector<PlatformerEntity*> playerEntities, std::vector<PlatformerEntity*> enemyEntities);

protected:
	CombatAIHelper();
	virtual ~CombatAIHelper();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;

private:
	typedef SmartNode super;

	void performRetargetCorrections(TimelineEntry* attackingEntry);
	void performAIActions(TimelineEntry* attackingEntry);
	void selectTarget(TimelineEntry* attackingEntry);
	void selectAttack(TimelineEntry* attackingEntry);

	struct AttackProbability
	{
		PlatformerAttack* attack;
		float cumulativeProbability;

		AttackProbability(PlatformerAttack* attack, float cumulativeProbability) : attack(attack), cumulativeProbability(cumulativeProbability) { }
	};

	struct ProbabilityMap
	{
		std::vector<AttackProbability> probabilities;
		float sum;

		ProbabilityMap() : probabilities({ }), sum(0.0f) { }
		ProbabilityMap(std::vector<AttackProbability> probabilities, float sum) : probabilities(probabilities), sum(sum) { }

		PlatformerAttack* getRandomAttack()
		{
			PlatformerAttack* attack = nullptr;
			float rng = cocos2d::RandomHelper::random_real(0.0f, sum);

			for (auto next : probabilities)
			{
				attack = next.attack;

				if (rng <= next.cumulativeProbability)
				{
					break;
				}
			}

			return attack;
		}
	};

	void trySelectResurrectionSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList);
	void trySelectHealingSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList);
	void trySelectDamageSkill(TimelineEntry* attackingEntry, const std::vector<PlatformerAttack*>& attackList);
	CombatAIHelper::ProbabilityMap buildCumulativeProbabilityMap(const std::vector<PlatformerAttack*>& attackList, std::function<bool(PlatformerAttack*)> predicate);

	std::vector<PlatformerEntity*> playerEntities;
	std::vector<PlatformerEntity*> enemyEntities;
	PlatformerEntity* selectedTarget;
	PlatformerAttack* selectedAttack;
};
