#include "soundtimelineinstance.h"

#include "../entity/entityinstancedata.h"

#include "timelinekey.h"

namespace SpriterEngine
{

	SoundTimelineInstance::SoundTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId) :
		TriggerTimelineInstance(entityInstanceData, timeline)
	{
		resultObject = entityInstanceData->getSoundObject(objectId);
	}

	void SoundTimelineInstance::checkTrigger(TimelineKey *key, real aTime, real bTime)
	{
		if (key->getObjectInfo()->getTriggerCount() && aTime <= key->getTime() && key->getTime() < bTime)
		{
			triggerCount++;
		}
	}

}
