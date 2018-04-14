#ifndef TRIGGERTIMELINEINSTANCE_H
#define TRIGGERTIMELINEINSTANCE_H

#include "timelineinstance.h"

namespace SpriterEngine
{

	class EntityInstanceData;

	class TriggerTimelineInstance : public TimelineInstance
	{
	public:
		TriggerTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline, int objectId);

		void findCurrentTimelineKey(real newTime, bool forward, real animationLength) override;

		void processCurrentTimelineKey(real newTime) override;

	protected:
		int triggerCount;

		TriggerTimelineInstance(EntityInstanceData *entityInstanceData, Timeline *timeline);

	private:
		void findTimeForward(real newTime, real animationLength);
		void findTimeBackward(real newTime, real animationLength);

		virtual void checkTrigger(TimelineKey * key, real aTime, real bTime);

		real previousTime;
	};

}

#endif // TRIGGERTIMELINEINSTANCE_H
