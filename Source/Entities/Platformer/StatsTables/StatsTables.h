#pragma once
#include <map>

#include "Engine/GlobalNode.h"

class PlatformerEntity;

class StatsTables : public GlobalNode
{
public:
	static void registerGlobalNode();

	static int getExpRequiredAtLevel(PlatformerEntity* platformerEntity);
	static int getKillExp(PlatformerEntity* platformerEntity);
	static int getBaseMana(PlatformerEntity* platformerEntity);
	static int getBaseHealth(PlatformerEntity* platformerEntity);

protected:
	StatsTables();
	virtual ~StatsTables();

private:
	typedef GlobalNode super;

	struct Stats
	{
		int health;
		int mana;
		int exp;
		std::vector<std::tuple<int, int, int>> increments;

		Stats() : health(665), mana(68), exp(419), increments({ }) { }
		Stats(int health, int mana, int exp) : health(health), mana(mana), exp(exp), increments({ }) { }
		Stats(int health, int mana, int exp, std::vector<std::tuple<int, int, int>> increments) : health(health), mana(mana), exp(exp), increments(increments) { }
	};

	static StatsTables* getInstance();

	static StatsTables* instance;
	static std::map<std::string, Stats> StatsTable;
	static const int FallbackExp;
	static const int FallbackMana;
	static const int FallbackHealth;
};
