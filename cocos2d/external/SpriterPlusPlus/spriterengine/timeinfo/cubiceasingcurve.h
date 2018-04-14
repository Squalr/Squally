#ifndef CUBICEASINGCURVE_H
#define CUBICEASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class CubicEasingCurve : public EasingCurveInterface
	{
	public:
		CubicEasingCurve(real initialC0, real initialC1);

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;

	private:
		real c0;
		real c1;
	};

}

#endif // CUBICEASINGCURVE_H
