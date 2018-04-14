#include "variabletimelineinstance.h"

#include "../entity/entityinstancedata.h"

namespace SpriterEngine
{

	VariableTimelineInstance::VariableTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId, int initialVariableId) :
		TimelineInstance(timeline)
	{
		resultObject = entityInstanceData->getVariable(objectId, initialVariableId);
	}

}
