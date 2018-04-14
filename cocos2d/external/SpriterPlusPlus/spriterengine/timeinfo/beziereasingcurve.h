#ifndef BEZIEREASINGCURVE_H
#define BEZIEREASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class BezierEasingCurve : public EasingCurveInterface
	{
	public:
		BezierEasingCurve(real initialX1, real initialY1, real initialX2, real initialY2);

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;

	private:
		real sampleCurve(real a, real b, real c, real t) const;
		real sampleCurveDerivativeX(real ax, real bx, real cx, real t) const;
		real solveEpsilon(real duration) const;
		real solve(real ax, real bx, real cx, real ay, real by, real cy, real x, real epsilon) const;
		real solveCurveX(real ax, real bx, real cx, real x, real epsilon) const;
		real cubicBezierAtTime(real t) const;

		real x1;
		real y1;
		real x2;
		real y2;
	};

}

#endif // BEZIEREASINGCURVE_H
