#ifndef VARIABLETIMELINEINSTANCE_H
#define VARIABLETIMELINEINSTANCE_H

#include "timelineinstance.h"

namespace SpriterEngine
{

	class EntityInstanceData;

	class VariableTimelineInstance : public TimelineInstance
	{
	public:
		VariableTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId, int initialVariableId);
	};

}

#endif // VARIABLETIMELINEINSTANCE_H
