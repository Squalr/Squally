#ifndef INTVARIABLEINFO_H
#define INTVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class IntVariableInfo : public UniversalObjectInterface
	{
	public:
		IntVariableInfo();

		int getIntValue() override;
		void setIntValue(int newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		int value;
	};

}

#endif // INTVARIABLEINFO_H
