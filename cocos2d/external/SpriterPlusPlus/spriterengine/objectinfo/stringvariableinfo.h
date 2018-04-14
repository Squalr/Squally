#ifndef STRINGVARIABLEINFO_H
#define STRINGVARIABLEINFO_H

#include "universalobjectinterface.h"

namespace SpriterEngine
{

	class StringVariableInfo : public UniversalObjectInterface
	{
	public:
		StringVariableInfo();

		std::string getStringValue() override;
		void setStringValue(const std::string &newValue) override;

		void setObjectToLinear(UniversalObjectInterface *bObject, real t, UniversalObjectInterface *resultObject) override;

	private:
		std::string value;
	};

}

#endif // STRINGVARIABLEINFO_H
