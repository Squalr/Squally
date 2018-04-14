#ifndef QUARTICEASINGCURVE_H
#define QUARTICEASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class QuarticEasingCurve : public EasingCurveInterface
	{
	public:
		QuarticEasingCurve(real initialC0, real initialC1, real initialC2);

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;

	private:
		real c0;
		real c1;
		real c2;
	};

}

#endif // QUARTICEASINGCURVE_H
