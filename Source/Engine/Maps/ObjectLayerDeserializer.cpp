#include "ObjectLayerDeserializer.h"

#include "cocos/2d/CCTMXObjectGroup.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableLayer.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string ObjectLayerDeserializer::MapKeyObjectLayer = "objects";
ObjectLayerDeserializer* ObjectLayerDeserializer::instance = nullptr;

void ObjectLayerDeserializer::registerGlobalNode()
{
	if (ObjectLayerDeserializer::instance == nullptr)
	{
		ObjectLayerDeserializer::instance = new ObjectLayerDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(ObjectLayerDeserializer::instance);
	}
}

ObjectLayerDeserializer::ObjectLayerDeserializer()
{
}

ObjectLayerDeserializer::~ObjectLayerDeserializer()
{
}

void ObjectLayerDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addGlobalEventListener(deserializationRequestListener);
}

void ObjectLayerDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	ValueMap properties = args->objectGroup->getProperties();

	if (!GameUtils::keyExists(properties, SerializableLayer::KeyType))
	{
		return;
	}

	std::string type = properties.at(SerializableLayer::KeyType).asString();

	if (type != ObjectLayerDeserializer::MapKeyObjectLayer)
	{
		return;
	}

	std::vector<SerializableObject*> deserializedObjects = std::vector<SerializableObject*>();
	std::string name = args->objectGroup->getGroupName();
	ValueVector objects = args->objectGroup->getObjects();

	// Callback to receive deserialized layers as they are parsed by their deserializers
	auto onDeserializeCallback = [&](DeserializationEvents::ObjectDeserializationArgs args)
	{
		deserializedObjects.push_back(args.serializableObject);
	};

	// Fire deserialization events for objects
	for (int index = 0; index < objects.size(); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			ValueMap object = objects[index].asValueMap();
			std::string typeName = "";

			// Append additional map metadata properties to object at load time to assist in deserialization
			object[SerializableObject::MapKeyMetaIsIsometric] = args->mapMeta.isIsometric;
			object[SerializableObject::MapKeyMetaMapWidth] = args->mapMeta.mapSize.width;
			object[SerializableObject::MapKeyMetaMapHeight] = args->mapMeta.mapSize.height;
			object[SerializableObject::MapKeyMetaMapIdentifier] = args->mapMeta.mapIdentifier;

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyType))
			{
				CCLOG("Missing type on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyName))
			{
				CCLOG("Missing name on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyWidth))
			{
				CCLOG("Missing width on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyHeight))
			{
				CCLOG("Missing height on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyXPosition))
			{
				CCLOG("Missing x position on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::MapKeyYPosition))
			{
				CCLOG("Missing y position on object");
				continue;
			}

			typeName = object.at(SerializableObject::MapKeyType).asString();

			// Fire event requesting the deserialization of this object
			DeserializationEvents::TriggerRequestObjectDeserialize(DeserializationEvents::ObjectDeserializationRequestArgs(
				typeName,
				object,
				onDeserializeCallback
			));
		}
	}

	args->onDeserializeCallback(DeserializationEvents::LayerDeserializationArgs(SerializableLayer::create(properties, name, deserializedObjects), args->objectGroup->layerIndex));
}
