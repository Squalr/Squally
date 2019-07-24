#include "ObjectLayerDeserializer.h"

#include "cocos/base/CCValue.h"

#include "Engine/Deserializers/ObjectDeserializer.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string ObjectLayerDeserializer::MapKeyObjectLayer = "objects";

ObjectLayerDeserializer* ObjectLayerDeserializer::create(std::map<std::string, ObjectDeserializer*> objectDeserializers)
{
	ObjectLayerDeserializer* instance = new ObjectLayerDeserializer(objectDeserializers);

	instance->autorelease();

	return instance;
}

ObjectLayerDeserializer::ObjectLayerDeserializer(std::map<std::string, ObjectDeserializer*> objectDeserializers) : super(ObjectLayerDeserializer::MapKeyObjectLayer)
{
	this->objectDeserializers = objectDeserializers;
}

ObjectLayerDeserializer::~ObjectLayerDeserializer()
{
}

void ObjectLayerDeserializer::deserialize(LayerDeserializer::LayerDeserializationRequestArgs* args)
{
	std::vector<GameObject*> deserializedObjects = std::vector<GameObject*>();
	ValueMap properties = args->properties;
	std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();
	std::string type = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyType, Value("")).asString();
	ValueVector objects = args->objects;

	// Callback to receive deserialized layers as they are parsed by their deserializers
	auto onDeserializeCallback = [&](ObjectDeserializer::ObjectDeserializationArgs args)
	{
		deserializedObjects.push_back(args.gameObject);
	};

	// Fire deserialization events for objects
	for (int index = 0; index < objects.size(); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			ValueMap object = objects[index].asValueMap();

			// Append additional map metadata properties to object at load time to assist in deserialization
			object[GameObject::MapKeyMetaIsIsometric] = args->isIsometric;
			object[GameObject::MapKeyMetaMapWidth] = args->mapSize.width;
			object[GameObject::MapKeyMetaMapHeight] = args->mapSize.height;
			object[GameObject::MapKeyMetaMapIdentifier] = args->mapIdentifier;

			if (!GameUtils::keyExists(object, GameObject::MapKeyType))
			{
				CCLOG("Missing type on object");
				continue;
			}

			if (!GameUtils::keyExists(object, GameObject::MapKeyName))
			{
				CCLOG("Missing name on object");
				continue;
			}

			if (!GameUtils::keyExists(object, GameObject::MapKeyWidth))
			{
				CCLOG("Missing width on object");
				continue;
			}

			if (!GameUtils::keyExists(object, GameObject::MapKeyHeight))
			{
				CCLOG("Missing height on object");
				continue;
			}

			if (!GameUtils::keyExists(object, GameObject::MapKeyXPosition))
			{
				CCLOG("Missing x position on object");
				continue;
			}

			if (!GameUtils::keyExists(object, GameObject::MapKeyYPosition))
			{
				CCLOG("Missing y position on object");
				continue;
			}

			std::string objectName = GameUtils::getKeyOrDefault(object, GameObject::MapKeyName, Value("")).asString();
			std::string objectType = GameUtils::getKeyOrDefault(object, GameObject::MapKeyType, Value("")).asString();

			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				object,
				onDeserializeCallback
			);

			if (objectDeserializers.find(objectType) != objectDeserializers.end())
			{
				objectDeserializers[objectType]->deserialize(&args);
			}
		}
	}

	args->onDeserializeCallback(LayerDeserializer::LayerDeserializationArgs(MapLayer::create(properties, name, type, deserializedObjects), args->layerIndex));
}
