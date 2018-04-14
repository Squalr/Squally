#ifndef SOUNDTIMELINEINSTANCE_H
#define SOUNDTIMELINEINSTANCE_H

#include "triggertimelineinstance.h"

namespace SpriterEngine
{

	class EntityInstanceData;
	class FileReference;

	class SoundTimelineInstance : public TriggerTimelineInstance
	{
	public:
		SoundTimelineInstance(EntityInstanceData *entityInstance, Timeline *timeline, int objectId);

	private:
		void checkTrigger(TimelineKey *key, real aTime, real bTime) override;
	};

}

#endif // SOUNDTIMELINEINSTANCE_H
