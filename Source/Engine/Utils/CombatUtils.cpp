#include "CombatUtils.h"

#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

int CombatUtils::GetLivingCount(const std::vector<PlatformerEntity*>& entities)
{
	int livingCount = 0;

	for (auto next : entities)
	{
		if (next->getRuntimeStateOrDefault(StateKeys::IsAlive, Value(true)).asBool())
		{
			livingCount++;
		}
	}

	return livingCount;
}

bool CombatUtils::HasDuplicateCastOnLivingTarget(PlatformerEntity* caster, PlatformerEntity* target, std::function<bool(PlatformerAttack*)> comparer)
{
	if (!target->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		return true;
	}

	return CombatUtils::HasDuplicateCastOnTarget(caster, target, comparer);
}

bool CombatUtils::HasDuplicateCastOnTarget(PlatformerEntity* caster, PlatformerEntity* target, std::function<bool(PlatformerAttack*)> comparer)
{
	bool hasDuplicateCast = false;

	CombatEvents::TriggerQueryTimeline(CombatEvents::QueryTimelineArgs([&](Timeline* timeline)
	{
		for (auto next : timeline->getSameTeamEntries(caster))
		{
			if (next->getEntity() == caster)
			{
				continue;
			}

			bool hasTarget = false;
			
			for (auto nextTarget : next->getStagedTargets())
			{
				if (target == nextTarget)
				{
					hasTarget = true;
				}
			}

			if (!hasTarget)
			{
				continue;
			}

			if (comparer(next->getStagedCast()))
			{
				hasDuplicateCast = true;
				break;
			}
		}
	}));

	return hasDuplicateCast;
}
