#ifndef TAGTIMELINEINSTANCE_H
#define TAGTIMELINEINSTANCE_H

#include "timelineinstance.h"

namespace SpriterEngine
{

	class EntityInstanceData;

	class TagTimelineInstance : public TimelineInstance
	{
	public:
		TagTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId);
	};

}

#endif // TAGTIMELINEINSTANCE_H
