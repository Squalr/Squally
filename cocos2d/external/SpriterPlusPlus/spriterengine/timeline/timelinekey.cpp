#include "timelinekey.h"

#include "../objectinfo/universalobjectinterface.h"
#include "../timeinfo/timeinfo.h"

#include "../timeinfo/instanteasingcurve.h"

#include "proxytimelinekey.h"

namespace SpriterEngine
{

	TimelineKey::TimelineKey(TimeInfo *initialTimeInfo, UniversalObjectInterface *initialObjectInfo) :
		time(initialTimeInfo),
		objectInfo(initialObjectInfo),
		nextObjectInfo(0)
	{
	}

	TimelineKey::~TimelineKey()
	{
		delete time;
		if (objectInfo)
		{
			delete objectInfo;
		}
	}

	void TimelineKey::process(real currentTime, UniversalObjectInterface *resultObject)
	{
		objectInfo->setObjectToLinear(nextObjectInfo, time->getTimeRatio(currentTime), resultObject);
	}

	void TimelineKey::blend(real currentTime, real blendRatio, UniversalObjectInterface *resultObject, ObjectRefInstance *refInstance)
	{
		resultObject->setToBlendedLinear(objectInfo, nextObjectInfo, time->getTimeRatio(currentTime), blendRatio, refInstance);
	}

	UniversalObjectInterface *TimelineKey::getObjectInfo()
	{
		return objectInfo;
	}

	void TimelineKey::setNextObjectInfo(UniversalObjectInterface *newNextObjectInfo)
	{
		nextObjectInfo = newNextObjectInfo;
	}

	real TimelineKey::getTime()
	{
		return time->getTime();
	}

	real TimelineKey::getNextTime()
	{
		return time->getNextTime();
	}

	bool TimelineKey::timeInRange(real timeToCheck)
	{
		return time->timeInRange(timeToCheck);
	}

	TimelineKey * TimelineKey::newProxyKey(real newTime, real newNextTime, bool makeInstant)
	{
		TimeInfo *newTimeInfo = 0;
		if (makeInstant)
		{
			newTimeInfo = new TimeInfo(newTime, newNextTime, new InstantEasingCurve());
		}
		else
		{
			newTimeInfo = time->cloneWithNewTimes(newTime, newNextTime);
		}
		return  new ProxyTimelineKey(newTimeInfo, objectInfo, nextObjectInfo);
	}

}
