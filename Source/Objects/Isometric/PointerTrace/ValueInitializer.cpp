#include "ValueInitializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"

using namespace cocos2d;

const std::string ValueInitializer::MapKeyValueInitializerPrefix = "value-";
const std::string ValueInitializer::MapKeyMetaValue = "value";

ValueInitializer* ValueInitializer::create(ValueMap& initProperties)
{
	ValueInitializer* instance = new ValueInitializer(initProperties);

	instance->autorelease();

	return instance;
}

ValueInitializer::ValueInitializer(ValueMap& initProperties) : super(initProperties)
{
	const std::string name = GameUtils::getKeyOrDefault(this->properties, SerializableObject::MapKeyName, Value("")).asString();
	
	std::string valueString = StrUtils::ltrim(name, ValueInitializer::MapKeyValueInitializerPrefix);

	this->value = StrUtils::isInteger(valueString) ? std::stoi(valueString) : 0;
}

ValueInitializer::~ValueInitializer()
{
}

void ValueInitializer::setGridIndex(int gridIndex)
{
	super::setGridIndex(gridIndex);
}
