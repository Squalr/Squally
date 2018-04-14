#ifndef EASINGCURVEINTERFACE_H
#define EASINGCURVEINTERFACE_H

#include "../global/global.h"

namespace SpriterEngine
{

	class EasingCurveInterface
	{
	public:
		EasingCurveInterface();
		virtual ~EasingCurveInterface();

		virtual real adjustedTimeRatio(real timeRatio) = 0;

		virtual EasingCurveInterface *clone() = 0;
	};

}

#endif // EASINGCURVEINTERFACE_H
