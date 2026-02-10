#include "TerrainEvents.h"

#include "base/CCDirector.h"
#include "base/CCEventDispatcher.h"

using namespace cocos2d;

const std::string TerrainEvents::EventResolveOverlapConflicts = "EVENT_RESOLVE_OVERLAP_CONFLICTS";

void TerrainEvents::TriggerResolveOverlapConflicts(TerrainOverlapArgs args)
{
	Director::getInstance()->getEventDispatcher()->dispatchEvent(
		TerrainEvents::EventResolveOverlapConflicts,
		&args
	);
}
