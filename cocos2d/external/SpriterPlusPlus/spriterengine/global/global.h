#ifndef GLOBAL_H
#define GLOBAL_H

//With Android NDK & gnustl, std::to_string is not defined so fill it in here
#if defined(ANDROID) && defined(__GXX_EXPERIMENTAL_CXX0X__) && !defined(_GLIBCXX_USE_C99)
#include <sstream>
namespace std {
	template <typename T>
	inline std::string to_string(T value)
	{
		std::ostringstream os;
		os << value;
		return os.str();
	}
}
#endif //ANDROID

namespace SpriterEngine
{

	typedef double real;

	const int THIS_ENTITY = -1;
	const int OUT_OF_RANGE = - 1;

	const real ONEEIGHTY_OVER_PI = 57.295779513082320876798154814105;

	const real MAX_RADIANS = 6.28318530718;

	inline real toRadians(real angleInDegrees)
	{
		return angleInDegrees / ONEEIGHTY_OVER_PI;
	}

	inline real toDegrees(real angleInRadians)
	{
		return angleInRadians * ONEEIGHTY_OVER_PI;
	}

	inline real linear(real a, real b, real t)
	{
		return ((b - a)*t) + a;
	}

	inline real shortestAngleLinear(real a, real b, real t)
	{
		while (b - a < -(MAX_RADIANS /2.0))
		{
			a -= MAX_RADIANS;
		}
		while (b - a >(MAX_RADIANS / 2.0))
		{
			b -= MAX_RADIANS;
		}

		real result = linear(a, b, t);

		while (result < 0)
		{
			result += MAX_RADIANS;
		}
		while (result > MAX_RADIANS)
		{
			result -= MAX_RADIANS;
		}

		return result;
	}

	inline real inverseLinear(real a, real b, real x)
	{
		return (x - a) / (b - a);
	}

	inline real quadratic(real a, real b, real c, real t)
	{
		return linear(linear(a, b, t), linear(b, c, t), t);
	}

	inline real cubic(real a, real b, real c, real d, real t)
	{
		return linear(quadratic(a, b, c, t), quadratic(b, c, d, t), t);
	}

	inline real quartic(real a, real b, real c, real d, real e, real t)
	{
		return linear(cubic(a, b, c, d, t), cubic(b, c, d, e, t), t);
	}

	inline real quintic(real a, real b, real c, real d, real e, real f, real t)
	{
		return linear(quartic(a, b, c, d, e, t), quartic(b, c, d, e, f, t), t);
	}

	struct point
	{
		point(real initialX = 0, real initialY = 0) :
			x(initialX),
			y(initialY)
		{
		}

		real x;
		real y;
	};

	inline point linear(const point &a, const point &b, real t)
	{
		return point(linear(a.x, b.x, t), linear(a.y, b.y, t));
	}

	inline point add(const point &a, const point &b)
	{
		return point(a.x + b.x, a.y + b.y);
	}

	inline point multiply(const point &a, const point &b)
	{
		return point(a.x * b.x, a.y * b.y);
	}

}
#endif // GLOBAL_H
