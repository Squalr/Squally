#pragma once

#include "cocos/base/ccRandom.h"

#include "Engine/SmartNode.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

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
	void selectTargets(TimelineEntry* attackingEntry);
	void selectTargetSingle(TimelineEntry* attackingEntry);
	void selectTargetSelf(TimelineEntry* attackingEntry);
	void selectTargetsMulti(TimelineEntry* attackingEntry);
	void selectTargetsTeam(TimelineEntry* attackingEntry);
	void selectTargetsAll(TimelineEntry* attackingEntry);
	void selectAttack(TimelineEntry* attackingEntry);
	void shuffleEntities();

	struct AttackProbability
	{
		PlatformerAttack* attack = nullptr;
		float cumulativeProbability = 0.0f;

		AttackProbability(PlatformerAttack* attack, float cumulativeProbability) : attack(attack), cumulativeProbability(cumulativeProbability) { }
	};

	struct ProbabilityMap
	{
		std::vector<AttackProbability> probabilities;
		float sum = 0.0f;

		ProbabilityMap() { }
		ProbabilityMap(std::vector<AttackProbability> probabilities, float sum) : probabilities(probabilities), sum(sum) { }

		PlatformerAttack* getRandomAttack()
		{
			// Short circuit for guaranteed attacks
			for (AttackProbability& next : probabilities)
			{
				if (next.attack->getPriority() == PlatformerAttack::Priority::Guaranteed)
				{
					return next.attack;
				}
			}

			PlatformerAttack* attack = nullptr;
			float rng = cocos2d::RandomHelper::random_real(0.0f, sum);

			// Choose ability randomly
			for (AttackProbability& next : probabilities)
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
	std::vector<PlatformerEntity*> selectedTargets;
	PlatformerAttack* selectedAttack = nullptr;
};
