#include "StatsTables.h"

#include "Resources/UIResources.h"

const std::map<int, int> StatsTables::HealthGain =
{
	{ 1, 2 },
	{ 2, 2 },
	{ 3, 2 },
	{ 4, 2 },
	{ 5, 2 },
	{ 6, 3 },
	{ 7, 3 },
	{ 8, 3 },
	{ 9, 3 },
	{ 10, 3 },
	{ 11, 4 },
	{ 12, 4 },
	{ 13, 4 },
	{ 14, 4 },
	{ 15, 5 },
	{ 16, 5 },
	{ 17, 5 },
	{ 18, 5 },
	{ 19, 5 },
	{ 20, 5 }
};

const std::map<int, int> StatsTables::ManaGain =
{
	{ 1, 1 },
	{ 2, 1 },
	{ 3, 1 },
	{ 4, 1 },
	{ 5, 1 },
	{ 6, 1 },
	{ 7, 1 },
	{ 8, 1 },
	{ 9, 1 },
	{ 10, 1 },
	{ 11, 2 },
	{ 12, 2 },
	{ 13, 2 },
	{ 14, 2 },
	{ 15, 2 },
	{ 16, 2 },
	{ 17, 2 },
	{ 18, 2 },
	{ 19, 2 },
	{ 20, 2 }
};

const std::map<int, int> StatsTables::ExpRequired =
{
	{ 1, 64 },
	{ 2, 640 },
	{ 3, 1024 },
	{ 4, 1528 },
	{ 5, 2048 },
	{ 6, 3072 },
	{ 7, 3584 },
	{ 8, 4096 },
	{ 9, 4608 },
	{ 10, 5120 },
	{ 11, 5632 },
	{ 12, 6144 },
	{ 13, 6656 },
	{ 14, 7168 },
	{ 15, 7680 },
	{ 16, 8192 },
	{ 17, 8704 },
	{ 18, 9216 },
	{ 19, 9728 },
	{ 20, 10240 }
};

int StatsTables::getHealthGainAtLevel(int level)
{
	if (StatsTables::HealthGain.find(level) != StatsTables::HealthGain.end())
	{
		return StatsTables::HealthGain.at(level);
	}
	
	return 0;
}

int StatsTables::getHealthGainAtNewLevel(int newLevel)
{
	return StatsTables::getHealthGainAtLevel(newLevel - 1);
}

int StatsTables::getManaGainAtLevel(int level)
{
	if (StatsTables::ManaGain.find(level) != StatsTables::ManaGain.end())
	{
		return StatsTables::ManaGain.at(level);
	}
	
	return 0;
}

int StatsTables::getManaGainAtNewLevel(int newLevel)
{
	return StatsTables::getManaGainAtLevel(newLevel - 1);
}

int StatsTables::getExpRequiredAtLevel(int level)
{
	if (StatsTables::ExpRequired.find(level) != StatsTables::ExpRequired.end())
	{
		return StatsTables::ExpRequired.at(level);
	}
	
	return 0;
}

int StatsTables::calculateEnemyExp(int health, int mana)
{
	return health * 2 + mana;
}
