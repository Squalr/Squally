#pragma once
#include <map>

#include "Engine/GlobalNode.h"

class PlatformerEntity;

class StatsTables : public GlobalNode
{
public:
	static void RegisterGlobalNode();
	
	struct Stats
	{
		int health = 0;
		int mana = 0;
		int attack = 0;
		int magicAttack = 0;
		int armor = 0;
		float speed = 0.0f;
		int exp = 0;

		Stats() { }
		Stats(int health, int mana, int exp) : health(health), mana(mana), attack(0), magicAttack(0), armor(0), speed(0.0f), exp(exp) { }
		Stats(int health, int mana, int attack, int magicAttack, int armor, float speed, int exp)
			: health(health), mana(mana), attack(attack), magicAttack(magicAttack), armor(armor), speed(speed), exp(exp) { }
	};

	static int getExpRequiredAtLevel(PlatformerEntity* platformerEntity);
	static int getKillExp(PlatformerEntity* platformerEntity);
	static int getBaseMana(PlatformerEntity* platformerEntity);
	static int getBaseHealth(PlatformerEntity* platformerEntity);
	static Stats getBonusStats(PlatformerEntity* platformerEntity);

protected:
	StatsTables();
	virtual ~StatsTables();

private:
	typedef GlobalNode super;

	struct StatsIncrements
	{
		Stats baseStats;
		std::vector<Stats> increments;

		StatsIncrements() : baseStats(Stats()), increments({ }) { }
		StatsIncrements(Stats baseStats) : baseStats(baseStats), increments({ }) { }
		StatsIncrements(Stats baseStats, std::vector<Stats> increments) : baseStats(baseStats), increments(increments) { }
	};

	static StatsTables* getInstance();

	static StatsTables* Instance;
	static std::map<std::string, StatsIncrements> StatsTable;
	static const int FallbackExp;
	static const int FallbackMana;
	static const int FallbackHealth;
};
