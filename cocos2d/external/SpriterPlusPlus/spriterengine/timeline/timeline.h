#ifndef TIMELINE_H
#define TIMELINE_H

#include <vector>

#include "timelinekey.h"

namespace SpriterEngine
{

	class TimelineInstance;

	typedef std::vector<TimelineKey*> TimelineKeyVector;

	class Timeline
	{
	public:
		Timeline(int initialObjectId);
		~Timeline();

		int getObjectId();

		TimelineKey *pushBackKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo);

		TimelineKey * pushFrontProxyKey(real initialTime, real initialNextTime, bool isLooping);

		TimelineKey *getKey(int keyIndex);

		TimelineKey * getLastKey();

		void setupTimelineInstance(TimelineKeyVector **keyInstances);

	private:
		int objectId;

		TimelineKeyVector keys;
	};

}

#endif // TIMELINE_H
