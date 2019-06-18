#pragma once
#include <map>

class StatsTables
{
public:
	static int getHealthGainAtNewLevel(int newLevel);
	static int getManaGainAtNewLevel(int newLevel);
	static int getExpRequiredAtNewLevel(int newLevel);

protected:

private:
	static const std::map<int, int> HealthGain;
	static const std::map<int, int> ManaGain;
	static const std::map<int, int> ExpRequired;
};
