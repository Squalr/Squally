#include "timeinfo.h"

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	TimeInfo::TimeInfo(real initialTime, real initialNextTime, EasingCurveInterface *initialEasingCurve) :
		time(initialTime),
		nextTime(initialNextTime),
		easingCurve(initialEasingCurve)
	{
	}

	TimeInfo::~TimeInfo()
	{
		delete easingCurve;
	}

	real TimeInfo::getTime()
	{
		return time;
	}

	real TimeInfo::getNextTime()
	{
		return nextTime;
	}

	bool TimeInfo::timeInRange(real timeToCheck)
	{
		return time <= timeToCheck && timeToCheck < nextTime;
	}

	real TimeInfo::getTimeRatio(real currentTime)
	{
		return easingCurve->adjustedTimeRatio(inverseLinear(time, nextTime, currentTime));
	}

	real TimeInfo::getEasedTime(real currentTime)
	{
		return linear(time, nextTime, getTimeRatio(currentTime));
	}

	TimeInfo * TimeInfo::cloneWithNewTimes(real initialTime, real initialNextTime)
	{
		return new TimeInfo(initialTime, initialNextTime, easingCurve->clone());
	}

}
