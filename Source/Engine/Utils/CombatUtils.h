#pragma once

#include <vector>

class PlatformerEntity;

class CombatUtils
{
public:
	static int GetLivingCount(const std::vector<PlatformerEntity*>& entities);
};
