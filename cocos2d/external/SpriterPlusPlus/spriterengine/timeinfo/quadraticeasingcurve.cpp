#include "quadraticeasingcurve.h"

#include "../global/global.h"

namespace SpriterEngine
{

	QuadraticEasingCurve::QuadraticEasingCurve(real initialC0) :
		c0(initialC0)
	{
	}

	real QuadraticEasingCurve::adjustedTimeRatio(SpriterEngine::real timeRatio)
	{
		return quadratic(0, c0, 1, timeRatio);
	}

	EasingCurveInterface * QuadraticEasingCurve::clone()
	{
		return new QuadraticEasingCurve(c0);
	}

}
