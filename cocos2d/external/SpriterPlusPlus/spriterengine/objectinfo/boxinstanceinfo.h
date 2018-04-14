#ifndef BOXINSTANCEINFO_H
#define BOXINSTANCEINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class BoxInstanceInfo : public UniversalObjectInterface
	{
	public:
		BoxInstanceInfo(point initialSize);

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		point getPivot() override;
		point getSize() override;
		real getAlpha() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setPivot(const point &newPivot) override;
		void setAlpha(real newAlpha) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

		void render() override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		point pivot;

		point size;
	};

}

#endif // BOXINSTANCEINFO_H
