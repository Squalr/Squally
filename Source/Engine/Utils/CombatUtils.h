#pragma once

#include <functional>
#include <vector>

class PlatformerAttack;
class PlatformerEntity;

class CombatUtils
{
public:
	static int GetLivingCount(const std::vector<PlatformerEntity*>& entities);
	static bool HasDuplicateCastOnLivingTarget(PlatformerEntity* caster, PlatformerEntity* target, std::function<bool(PlatformerAttack*)> comparer);
	static bool HasDuplicateCastOnTarget(PlatformerEntity* caster, PlatformerEntity* target, std::function<bool(PlatformerAttack*)> comparer);
};
