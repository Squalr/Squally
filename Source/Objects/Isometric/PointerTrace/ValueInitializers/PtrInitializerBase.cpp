#include "PtrInitializerBase.h"

#include<regex>

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/PointerTraceEvents.h"

using namespace cocos2d;

const std::string PtrInitializerBase::OffsetRegex = "(\\+|\\-)?( .+)?[0-9]+";
const std::string PtrInitializerBase::IntegerRegex = "[0-9]+";

PtrInitializerBase::PtrInitializerBase(ValueMap& properties) : super(properties)
{
	std::string name = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyName, Value("")).asString();
	this->offset = 0;
    
	// A bit hackathon-esque, but it works. Extracts the offset integer from the string.
    std::regex re = std::regex(PtrInitializerBase::OffsetRegex);
    std::smatch match = std::smatch();

	if (std::regex_search(name, match, re))
	{
        if (match.ready())
		{
            std::string offsetStr = match[0];
			bool negate = false;

			if (StrUtils::startsWith(offsetStr, "-", true))
			{
				negate = true;
			}

			std::regex re2 = std::regex(PtrInitializerBase::IntegerRegex);
			std::smatch match2 = std::smatch();

			if (std::regex_search(offsetStr, match2, re2))
			{
				if (match2.ready())
				{
            		std::string integerStr = match2[0];

					if (StrUtils::isInteger(integerStr))
					{
						this->offset = std::stoi(integerStr);
					}
				}
			}

			if (negate)
			{
				this->offset *= -1;
			}
        }
    }
}

PtrInitializerBase::~PtrInitializerBase()
{
}
