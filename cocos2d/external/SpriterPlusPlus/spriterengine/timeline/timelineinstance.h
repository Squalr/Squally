#ifndef TIMELINEINSTANCE_H
#define TIMELINEINSTANCE_H

#include <vector>

#include "../global/global.h"

namespace SpriterEngine
{

	class EntityInstance;
	class UniversalObjectInterface;
	class Timeline;
	class TimelineKey;

	typedef std::vector<TimelineKey*> TimelineKeyVector;
	typedef TimelineKeyVector::iterator TimelineKeyVectorIterator;

	class TimelineInstance
	{
	public:
		TimelineInstance(Timeline *timeline);

		virtual ~TimelineInstance() = 0;

		virtual void findCurrentTimelineKey(real newTime, bool forward, real animationLength);
		virtual void processCurrentTimelineKey(real newTime);

		virtual void blendCurrentTimelineKey(real newTime, real blendRatio);

	protected:
		TimelineKeyVector *timelineKeys;
		TimelineKeyVectorIterator timelineKeyIterator;
		UniversalObjectInterface *resultObject;

	private:
		void findTimeForward(real newTime);
		void findTimeBackward(real newTime);
	};

}

#endif // TIMELINEINSTANCE_H
