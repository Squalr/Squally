#include "StatsTables.h"

#include "Resources/UIResources.h"

const std::map<int, int> StatsTables::HealthGain =
{
	{ 1, 25 },
};

const std::map<int, int> StatsTables::ManaGain =
{
	{ 1, 25 },
};

const std::map<int, int> StatsTables::ExpRequired =
{
	{ 1, 25 },
};

int StatsTables::getHealthGainAtNewLevel(int newLevel)
{
	if (StatsTables::HealthGain.find(newLevel) != StatsTables::HealthGain.end())
	{
		return StatsTables::HealthGain.at(newLevel);
	}
	
	return 0;
}

int StatsTables::getManaGainAtNewLevel(int newLevel)
{
	if (StatsTables::ManaGain.find(newLevel) != StatsTables::ManaGain.end())
	{
		return StatsTables::ManaGain.at(newLevel);
	}
	
	return 0;
}

int StatsTables::getExpRequiredAtNewLevel(int newLevel)
{
	if (StatsTables::ExpRequired.find(newLevel) != StatsTables::ExpRequired.end())
	{
		return StatsTables::ExpRequired.at(newLevel);
	}
	
	return 0;
}
