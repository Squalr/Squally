#ifndef ENTITYOBJECTINFO_H
#define ENTITYOBJECTINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class EntityObjectInfo : public UniversalObjectInterface
	{
	public:
		EntityObjectInfo();

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		real getAlpha() override;

		real getTimeRatio() override;


		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;
		void setSpin(int newSpin) override;

		void setTimeRatio(real newCurrentTimeRatio) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		real alpha;

		real timeRatio;
	};

}

#endif // ENTITYOBJECTINFO_H
