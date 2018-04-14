#include "stringvariableinforeference.h"

namespace SpriterEngine
{

	StringVariableInfoReference::StringVariableInfoReference() :
		value(0)
	{
	}

	std::string StringVariableInfoReference::getStringValue()
	{
		if (value)
		{
			return *value;
		}
		else
		{
			return "";
		}
	}

	void StringVariableInfoReference::setStringValue(std::string *newValue)
	{
		value = newValue;
	}

	void StringVariableInfoReference::setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance)
	{
		if (blendRatio >= 0.5)
		{
			aObject->setObjectToLinear(bObject, t, this);
		}
	}
}
