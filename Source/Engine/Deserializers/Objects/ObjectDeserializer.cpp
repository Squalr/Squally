#include "ObjectDeserializer.h"

#include "Engine/Deserializers/Properties/PropertyDeserializer.h"
#include "Engine/DeveloperMode/DeveloperModeController.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

ObjectDeserializer::ObjectDeserializer(std::string objectType, std::vector<PropertyDeserializer*> propertyDeserializers)
{
	this->objectType = objectType;
	this->propertyDeserializers = propertyDeserializers;

	for (auto next : this->propertyDeserializers)
	{
		if (next != nullptr)
		{
			this->addChild(next);
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

void ObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs args)
{
	this->deserialize(&args);
}

void ObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	const std::string name = GameUtils::getKeyOrDefault(args->properties, GameObject::MapKeyName, Value("")).asString();

	if (this->deserializers.find(name) != this->deserializers.end())
	{
		GameObject* object = this->deserializers[name](args->properties);

		this->deserializeProperties(object, args->properties);

		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(object));
	}
}

void ObjectDeserializer::deserializeProperties(GameObject* object, const ValueMap& properties)
{
	for (auto next : this->propertyDeserializers)
	{
		std::string key = GameUtils::getKeyOrDefault(properties, next->getPropertyDeserializerKey(), Value("")).asString();

		if (!key.empty())
		{
			next->deserializeProperties(object, properties);
		}
	}
}
