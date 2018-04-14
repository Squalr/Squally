#include "quinticeasingcurve.h"

namespace SpriterEngine
{

	QuinticEasingCurve::QuinticEasingCurve(real initialC0, real initialC1, real initialC2, real initialC3) :
		c0(initialC0),
		c1(initialC1),
		c2(initialC2),
		c3(initialC3)
	{
	}

	real QuinticEasingCurve::adjustedTimeRatio(real timeRatio)
	{
		return quintic(0, c0, c1, c2, c3, 1, timeRatio);
	}

	EasingCurveInterface * QuinticEasingCurve::clone()
	{
		return new QuinticEasingCurve(c0, c1, c2, c3);
	}

}
