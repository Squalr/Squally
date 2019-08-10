#pragma once
#include <map>

#include "Engine/GlobalNode.h"

class PlatformerEntity;

class StatsTables : public GlobalNode
{
public:
	static void registerGlobalNode();

	static int getHealthGainAtLevel(int level);
	static int getHealthGainAtNewLevel(int newLevel);
	static int getManaGainAtLevel(int level);
	static int getManaGainAtNewLevel(int newLevel);
	static int getExpRequiredAtLevel(int level);
	static int getExpNeededUntilLevel(int currentLevel, int currentExp, int level);
	static int getKillExp(PlatformerEntity* platformerEntity);
	static int getBaseMana(PlatformerEntity* platformerEntity);
	static int getBaseHealth(PlatformerEntity* platformerEntity);

protected:

private:
	typedef GlobalNode super;

	struct Stats
	{
		int health;
		int mana;
		int exp;

		Stats() : health(420), mana(420), exp(420) { }
		Stats(int health, int mana, int exp) : health(health), mana(mana), exp(exp) { }
	};

	static StatsTables* getInstance();
	StatsTables();
	~StatsTables();

	static StatsTables* instance;
	static const std::map<int, int> HealthGain;
	static const std::map<int, int> ManaGain;
	static const std::map<int, int> ExpRequired;
	static std::map<std::string, Stats> StatsTable;
	static const int FallbackExp;
	static const int FallbackMana;
	static const int FallbackHealth;
};
