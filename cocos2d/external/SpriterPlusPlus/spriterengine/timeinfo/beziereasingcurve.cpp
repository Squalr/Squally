#include "beziereasingcurve.h"

#include <cmath>

namespace SpriterEngine
{

	BezierEasingCurve::BezierEasingCurve(real initialX1, real initialY1, real initialX2, real initialY2) :
		x1(initialX1),
		y1(initialY1),
		x2(initialX2),
		y2(initialY2)
	{
	}

	real BezierEasingCurve::adjustedTimeRatio(real timeRatio)
	{
		return cubicBezierAtTime(timeRatio);
	}

	EasingCurveInterface * BezierEasingCurve::clone()
	{
		return new BezierEasingCurve(x1, y1, x2, y2);
	}

	real BezierEasingCurve::sampleCurve(real a, real b, real c, real t)const
	{
		return ((a*t + b)*t + c)*t;
	}

	real BezierEasingCurve::sampleCurveDerivativeX(real ax, real bx, real cx, real t) const
	{
		return (3.0*ax*t + 2.0*bx)*t + cx;
	}

	// The epsilon value to pass given that the animation is going to run over |dur| seconds. The longer the
	// animation, the more precision is needed in the timing function result to avoid ugly discontinuities.
	real BezierEasingCurve::solveEpsilon(real duration) const
	{
		return 1.0 / (200.0*duration);
	}

	real BezierEasingCurve::solve(real ax, real bx, real cx, real ay, real by, real cy, real x, real epsilon) const
	{
		return sampleCurve(ay, by, cy, solveCurveX(ax, bx, cx, x, epsilon));
	}

	// Given an x value, find a parametric value it came from.
	real BezierEasingCurve::solveCurveX(real ax, real bx, real cx, real x, real epsilon) const
	{
		real t0;
		real t1;
		real t2;
		real x2;
		real d2;
		int i;

		// First try a few iterations of Newton's method -- normally very fast.
		for (t2 = x, i = 0; i < 8; i++)
		{
			x2 = sampleCurve(ax, bx, cx, t2) - x;
			if (std::abs(x2) < epsilon)
			{
				return t2;
			}

			d2 = sampleCurveDerivativeX(ax, bx, cx, t2);

			if (std::abs(d2) < 1e-6)
			{
				break;
			}

			t2 = t2 - x2 / d2;
		}

		// Fall back to the bisection method for reliability.
		t0 = 0.0;
		t1 = 1.0;
		t2 = x;

		if (t2 < t0)
		{
			return t0;
		}

		if (t2 > t1)
		{
			return t1;
		}


		while (t0 < t1)
		{
			x2 = sampleCurve(ax, bx, cx, t2);
			if (std::abs(x2 - x) < epsilon)
			{
				return t2;
			}
			if (x > x2)
			{
				t0 = t2;
			}
			else
			{
				t1 = t2;
			}
			t2 = (t1 - t0)*.5 + t0;
		}

		return t2; // Failure.
	}

	real BezierEasingCurve::cubicBezierAtTime(real t) const
	{
		real duration = 1;
		real ax = 0;
		real bx = 0;
		real cx = 0;
		real ay = 0;
		real by = 0;
		real cy = 0;

		// `ax t^3 + bx t^2 + cx t' expanded using Horner's rule.
		// Calculate the polynomial coefficients, implicit first and last control points are (0,0) and (1,1).

		cx = 3.0*x1;
		bx = 3.0*(x2 - x1) - cx;
		ax = 1.0 - cx - bx;
		cy = 3.0*y1;
		by = 3.0*(y2 - y1) - cy;
		ay = 1.0 - cy - by;

		// Convert from input time to parametric value in curve, then from that to output time.
		return solve(ax, bx, cx, ay, by, cy, t, solveEpsilon(duration));
	}

}
