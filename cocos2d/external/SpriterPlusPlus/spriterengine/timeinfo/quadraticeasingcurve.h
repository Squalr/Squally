#ifndef QUADRATICEASINGCURVE_H
#define QUADRATICEASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class QuadraticEasingCurve : public EasingCurveInterface
	{
	public:
		QuadraticEasingCurve(real initialC0);

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;

	private:
		real c0;
	};

}

#endif // QUADRATICEASINGCURVE_H
