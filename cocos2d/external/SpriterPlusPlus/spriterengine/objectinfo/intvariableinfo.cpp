#include "intvariableinfo.h"

namespace SpriterEngine
{

	IntVariableInfo::IntVariableInfo() :
		value(0)
	{
	}

	int IntVariableInfo::getIntValue()
	{
		return value;
	}

	void IntVariableInfo::setIntValue(int newValue)
	{
		value = newValue;
	}

	void IntVariableInfo::setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject)
	{
		resultObject->setIntValue(int(linear(value, bObject->getIntValue(), t)));
	}

	void IntVariableInfo::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		int tempValue = value;

		aObject->setObjectToLinear(bObject, t, this);

		setIntValue(linear(tempValue, value, blendRatio));
	}

}
