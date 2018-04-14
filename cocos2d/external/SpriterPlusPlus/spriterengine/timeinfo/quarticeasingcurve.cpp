#include "quarticeasingcurve.h"

namespace SpriterEngine
{

	QuarticEasingCurve::QuarticEasingCurve(real initialC0, real initialC1, real initialC2) :
		c0(initialC0),
		c1(initialC1),
		c2(initialC2)
	{
	}


	SpriterEngine::real SpriterEngine::QuarticEasingCurve::adjustedTimeRatio(SpriterEngine::real timeRatio)
	{
		return quartic(0, c0, c1, c2, 1, timeRatio);
	}

	EasingCurveInterface * QuarticEasingCurve::clone()
	{
		return new QuarticEasingCurve(c0, c1, c2);
	}

}
