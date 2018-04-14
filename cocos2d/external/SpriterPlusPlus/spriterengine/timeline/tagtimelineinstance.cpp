#include "tagtimelineinstance.h"

#include "../entity/entityinstancedata.h"
#include "../objectinfo/tagobjectinforeference.h"

#include "timeline.h"

namespace SpriterEngine
{

	TagTimelineInstance::TagTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId) :
		TimelineInstance(timeline)
	{
		resultObject = entityInstanceData->getTags(objectId);
	}

}
