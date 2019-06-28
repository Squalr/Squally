#include "TerrainEvents.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string TerrainEvents::EventResolveOverlapConflicts = "EVENT_RESOLVE_OVERLAP_CONFLICTS";

void TerrainEvents::TriggerResolveOverlapConflicts(TerrainOverlapArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent(
		TerrainEvents::EventResolveOverlapConflicts,
		&args
	);
}
