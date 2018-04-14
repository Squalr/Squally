#ifndef QUINTICEASINGCURVE_H
#define QUINTICEASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class QuinticEasingCurve : public EasingCurveInterface
	{
	public:
		QuinticEasingCurve(real initialC0, real initialC1, real initialC2, real initialC3);

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;

	private:
		real c0;
		real c1;
		real c2;
		real c3;
	};

}

#endif // QUINTICEASINGCURVE_H
