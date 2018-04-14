#include "angleinfo.h"

namespace SpriterEngine
{

	AngleInfo::AngleInfo() :
		angle(0),
		spinDirection(0)
	{
	}

	real AngleInfo::angleLinear(real angleB, real t)
	{
		if (spinDirection == 0)
		{
			return angle;
		}

		if (spinDirection == 1)
		{
			if (angle < angleB)
			{
				angleB -= MAX_RADIANS;
			}
		}
		else
		{
			if (angleB < angle)
			{
				angleB += MAX_RADIANS;
			}
		}
		
		return linear(angle, angleB, t);
	}

}
