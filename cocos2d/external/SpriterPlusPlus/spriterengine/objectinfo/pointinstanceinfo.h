#ifndef POINTINSTANCEINFO_H
#define POINTINSTANCEINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class PointInstanceInfo : public UniversalObjectInterface
	{
	public:
		PointInstanceInfo();

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		real getAlpha() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setSpin(int newSpin) override;

		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

		void render() override;

	private:
		point position;
		AngleInfo angle;
	};

}

#endif // POINTINSTANCEINFO_H
