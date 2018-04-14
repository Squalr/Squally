#include "realvariableinfo.h"

namespace SpriterEngine
{

	RealVariableInfo::RealVariableInfo() :
		value(0)
	{
	}

	real RealVariableInfo::getRealValue()
	{
		return value;
	}

	void RealVariableInfo::setRealValue(real newValue)
	{
		value = newValue;
	}

	void RealVariableInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setRealValue(linear(value, bObject->getRealValue(), t));
	}

	void RealVariableInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		real tempValue = value;

		aObject->setObjectToLinear(bObject, t, this);

		setRealValue(linear(tempValue, value, blendRatio));
	}

}
