#include "CombatUtils.h"

#include "cocos/base/CCValue.h"

#include "Entities/Platformer/PlatformerEntity.h"
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
