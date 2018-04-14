#include "lineareasingcurve.h"

namespace SpriterEngine
{

	LinearEasingCurve::LinearEasingCurve()
	{
	}


	real LinearEasingCurve::adjustedTimeRatio(real timeRatio)
	{
		return timeRatio;
	}

	EasingCurveInterface * LinearEasingCurve::clone()
	{
		return new LinearEasingCurve();
	}

}
