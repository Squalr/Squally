#ifndef POINTOBJECTINFO_H
#define POINTOBJECTINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class PointObjectInfo : public UniversalObjectInterface
	{
	public:
		PointObjectInfo();

		point getPosition() override;
		real getAngle() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setSpin(int newSpin) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		point position;
		AngleInfo angle;
	};

}

#endif // POINTOBJECTINFO_H
