#ifndef TIMELINEKEY_H
#define TIMELINEKEY_H

#include "../global/global.h"

namespace SpriterEngine
{

	class TimeInfo;
	class UniversalObjectInterface;
	class ObjectRefInstance;

	class TimelineKey
	{
	public:
		TimelineKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo);
		virtual ~TimelineKey();

		void process(real currentTime, UniversalObjectInterface *resultObject);

		void blend(real currentTime, real blendRatio, UniversalObjectInterface * resultObject, ObjectRefInstance *refInstance = 0);

		UniversalObjectInterface *getObjectInfo();

		void setNextObjectInfo(UniversalObjectInterface *newNextObjectInfo);

		real getTime();
		real getNextTime();
		bool timeInRange(real timeToCheck);

		TimelineKey *newProxyKey(real newTime, real newNextTime, bool makeInstant);

	protected:
		UniversalObjectInterface *objectInfo;

	private:
		TimeInfo *time;
		UniversalObjectInterface *nextObjectInfo;
	};

}

#endif // TIMELINEKEY_H
