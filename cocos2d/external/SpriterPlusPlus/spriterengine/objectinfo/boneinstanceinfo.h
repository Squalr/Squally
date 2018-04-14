#ifndef BONEINSTANCEINFO_H
#define BONEINSTANCEINFO_H

#include "universalobjectinterface.h"

#include "angleinfo.h"

namespace SpriterEngine
{

	class BoneInstanceInfo : public UniversalObjectInterface
	{
	public:
		BoneInstanceInfo(point initialSize);

		point getPosition() override;
		real getAngle() override;
		point getScale() override;
		real getAlpha() override;

		point getSize() override;

		void setPosition(const point &newPosition) override;
		void setAngle(real newAngle) override;
		void setScale(const point &newScale) override;
		void setAlpha(real newAlpha) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

		void render() override;

	private:
		point position;
		AngleInfo angle;
		point scale;
		real alpha;

		point size;
	};

}

#endif // BONEINSTANCEINFO_H
