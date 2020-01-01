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

private:
	typedef SmartNode super;
	CombatAIHelper();
	virtual ~CombatAIHelper() = default;

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void update(float dt) override;

	void performRetargetCorrections(TimelineEntry* attackingEntry);
	void performAIActions(TimelineEntry* attackingEntry);
	void selectTarget(TimelineEntry* attackingEntry);
	void selectAttack(TimelineEntry* attackingEntry);

	struct ProbabilityMap
	{
		std::map<PlatformerAttack*, float> map;
		float sum;

		ProbabilityMap() : map({ }), sum(0.0f) { }
		ProbabilityMap(std::map<PlatformerAttack*, float> map, float sum) : map(map), sum(sum) { }

		PlatformerAttack* getRandomAttack()
		{
			PlatformerAttack* attack = nullptr;
			float rng = cocos2d::RandomHelper::random_real(0.0f, sum);

			for (auto next : map)
			{
				attack = next.first;

				if (next.second > rng)
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
