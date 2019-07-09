#include "ValueInitializer.h"

#include <regex>

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/PointerTraceEvents.h"

using namespace cocos2d;

const std::string ValueInitializer::MapKeyValueInitializerRegex = "value\\-[0-9]+";
const std::string ValueInitializer::MapKeyMetaValue = "value";
const std::string ValueInitializer::IntegerRegex = "[0-9]+";

ValueInitializer* ValueInitializer::create(ValueMap& initProperties)
{
	ValueInitializer* instance = new ValueInitializer(initProperties);

	instance->autorelease();

	return instance;
}

ValueInitializer::ValueInitializer(ValueMap& initProperties) : super(initProperties)
{
	std::string name = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyName, Value("")).asString();
	this->value = 0;
    
    std::regex re = std::regex(ValueInitializer::IntegerRegex);
    std::smatch match = std::smatch();

	if (std::regex_search(name, match, re))
	{
        if (match.ready())
		{
			std::string integerStr = match[0];

			if (StrUtils::isInteger(integerStr))
			{
				this->value = std::stoi(integerStr);
			}
        }
    }
}

ValueInitializer::~ValueInitializer()
{
}

void ValueInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);

	PointerTraceEvents::TriggerWriteValue(PointerTraceEvents::PointerTraceWriteArgs(gridIndex, this->value));
}
