#ifndef BOXOBJECTINFO_H
#define BOXOBJECTINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class BoxObjectInfo : public UniversalObjectInterface
	{
	public:
		BoxObjectInfo();

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		real getAlpha() override;
		point getPivot() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setPivot(const point &newPivot) override;
		void setSpin(int newSpin) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		point pivot;
		real alpha;
	};

}

#endif // BOXOBJECTINFO_H
