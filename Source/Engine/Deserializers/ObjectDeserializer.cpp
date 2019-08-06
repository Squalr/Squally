#include "ObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/PropertyDeserializer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

ObjectDeserializer::ObjectDeserializer(std::string objectType, std::vector<PropertyDeserializer*> propertyDeserializers)
{
	this->objectType = objectType;
	this->propertyDeserializers = propertyDeserializers;

	for (auto it = this->propertyDeserializers.begin(); it != this->propertyDeserializers.end(); it++)
	{
		if (*it != nullptr)
		{
			this->addChild(*it);
		}
	}
}

ObjectDeserializer::~ObjectDeserializer()
{
}

std::string ObjectDeserializer::getObjectType()
{
	return this->objectType;
}

void ObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	const std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();

	if (this->deserializers.find(name) != this->deserializers.end())
	{
		GameObject* object = this->deserializers[name](properties);

		for (auto it = this->propertyDeserializers.begin(); it != this->propertyDeserializers.end(); it++)
		{
			std::string key = GameUtils::getKeyOrDefault(properties, (*it)->getPropertyDeserializerKey(), Value("")).asString();

			if (!key.empty())
			{
				(*it)->deserializeProperties(object, properties);
			}
		}

		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(object));
	}
	else
	{
		CCLOG("Unknown entity encountered: %s", name.c_str());
	}
}
