#include "ObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/QuestDeserializer.h"

using namespace cocos2d;

ObjectDeserializer::ObjectDeserializer(std::string objectType, QuestDeserializer* questDeserializer)
{
	this->objectType = objectType;
	this->questDeserializer = questDeserializer;

	if (questDeserializer != nullptr)
	{
		this->addChild(this->questDeserializer);
	}
}

ObjectDeserializer::~ObjectDeserializer()
{
}

std::string ObjectDeserializer::getObjectType()
{
	return this->objectType;
}
