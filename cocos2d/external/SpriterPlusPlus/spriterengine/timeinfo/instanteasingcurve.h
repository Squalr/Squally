#ifndef INSTANTEASINGCURVE_H
#define INSTANTEASINGCURVE_H

#include "easingcurveinterface.h"

namespace SpriterEngine
{

	class InstantEasingCurve : public EasingCurveInterface
	{
	public:
		InstantEasingCurve();

		real adjustedTimeRatio(real timeRatio) override;

		EasingCurveInterface *clone() override;
	};

}

#endif // INSTANTEASINGCURVE_H
