#include "ObjectDeserializer.h"

#include "cocos/base/CCValue.h"

using namespace cocos2d;

ObjectDeserializer::ObjectDeserializer(std::string objectType)
{
	this->objectType = objectType;
}

ObjectDeserializer::~ObjectDeserializer()
{
}

std::string ObjectDeserializer::getObjectType()
{
	return this->objectType;
}
