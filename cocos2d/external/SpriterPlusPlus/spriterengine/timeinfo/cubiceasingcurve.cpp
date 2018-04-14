#include "cubiceasingcurve.h"

namespace SpriterEngine
{

	CubicEasingCurve::CubicEasingCurve(SpriterEngine::real initialC0, SpriterEngine::real initialC1) :
		c0(initialC0),
		c1(initialC1)
	{
	}

	real CubicEasingCurve::adjustedTimeRatio(real timeRatio)
	{
		return cubic(0, c0, c1, 1, timeRatio);
	}

	EasingCurveInterface * CubicEasingCurve::clone()
	{
		return new CubicEasingCurve(c0, c1);
	}

}
