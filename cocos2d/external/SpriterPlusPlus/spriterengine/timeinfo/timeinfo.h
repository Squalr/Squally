#ifndef TIMEINFO_H
#define TIMEINFO_H

#include "../global/global.h"

namespace SpriterEngine
{

	class EasingCurveInterface;

	class TimeInfo
	{
	public:
		TimeInfo(real initialTime, real initialNextTime, EasingCurveInterface *initialEasingCurve);
		~TimeInfo();

		real getTime();
		real getNextTime();
		bool timeInRange(real timeToCheck);
		real getTimeRatio(real currentTime);

		real getEasedTime(real currentTime);

		TimeInfo *cloneWithNewTimes(real initialTime, real initialNextTime);

	private:
		real time;
		real nextTime;

		EasingCurveInterface *easingCurve;
	};

}

#endif // TIMEINFO_H
