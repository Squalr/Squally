#ifndef STRINGVARIABLEINFOREFERENCE_H
#define STRINGVARIABLEINFOREFERENCE_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class StringVariableInfoReference : public UniversalObjectInterface
	{
	public:
		StringVariableInfoReference();

		std::string getStringValue() override;
		void setStringValue(std::string *newValue) override;

		void setToBlendedLinear(UniversalObjectInterface *aObject, UniversalObjectInterface *bObject, real t, real blendRatio, ObjectRefInstance *blendedRefInstance = 0) override;

	private:
		std::string *value;
	};

}

#endif // STRINGVARIABLEINFOREFERENCE_H
