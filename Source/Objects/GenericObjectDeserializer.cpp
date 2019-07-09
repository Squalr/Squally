#include "GenericObjectDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/GlobalDirector.h"
#include "Objects/GenericObjects.h"

using namespace cocos2d;

const std::string GenericObjectDeserializer::KeyTypeObject = "object";

GenericObjectDeserializer* GenericObjectDeserializer::create()
{
	GenericObjectDeserializer* instance = new GenericObjectDeserializer();

	instance->autorelease();

	return instance;
}

GenericObjectDeserializer::GenericObjectDeserializer() : super(GenericObjectDeserializer::KeyTypeObject)
{
}

GenericObjectDeserializer::~GenericObjectDeserializer()
{
}

void GenericObjectDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(GameObject::MapKeyName).asString();
	GameObject* newObject = nullptr;

	if (name == CameraFocus::MapKeyCameraFocus)
	{
		newObject = CameraFocus::create(properties);
	}
	else if (name == CameraScrollTracker::MapKeyCameraScrollTracker)
	{
		newObject = CameraScrollTracker::create(properties);
	}
	else
	{
		CCLOG("Missing properties on platformer object");
		return;
	}
	
	if (newObject != nullptr)
	{
		args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newObject));
	}
}
