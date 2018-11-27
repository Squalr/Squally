#include "LayerDeserializer.h"

LayerDeserializer* LayerDeserializer::instance = nullptr;

void LayerDeserializer::registerGlobalNode()
{
	if (LayerDeserializer::instance == nullptr)
	{
		LayerDeserializer::instance = new LayerDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(LayerDeserializer::instance);
	}
}

LayerDeserializer::LayerDeserializer()
{
}

LayerDeserializer::~LayerDeserializer()
{
}

void LayerDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestLayerDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::LayerDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void LayerDeserializer::onDeserializationRequest(DeserializationEvents::LayerDeserializationRequestArgs* args)
{
	static std::vector<SerializableObject*> deserializedObjects = std::vector<SerializableObject*>();
	std::string name = args->objectGroup->getGroupName();
	ValueVector objects = args->objectGroup->getObjects();
	ValueMap properties = args->objectGroup->getProperties();

	deserializedObjects.clear();

	// Add an event listener to the scene to receive deserialized layers as they are parsed by their deserializers
	Director::getInstance()->getRunningScene()->getEventDispatcher()->addCustomEventListener(
		DeserializationEvents::ObjectDeserializeEvent,
		[=](EventCustom* event)
		{
			DeserializationEvents::ObjectDeserializationArgs* args = (DeserializationEvents::ObjectDeserializationArgs*)event->getUserData();
			deserializedObjects.push_back(args->serializableObject);
		});

	// Fire deserialization events for objects
	for (int index = 0; index < objects.size(); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			ValueMap object = objects[index].asValueMap();
			std::string typeName = "";

			// Append additional map metadata properties to object at load time to assist in deserialization
			object[SerializableObject::KeyMetaIsIsometric] = args->mapMeta.isIsometric;
			object[SerializableObject::KeyMetaMapWidth] = args->mapMeta.mapSize.width;
			object[SerializableObject::KeyMetaMapHeight] = args->mapMeta.mapSize.height;

			if (!GameUtils::keyExists(&object, SerializableObject::KeyType))
			{
				CCLOG("Missing type on object");
				continue;
			}

			if (!GameUtils::keyExists(&object, SerializableObject::KeyName))
			{
				CCLOG("Missing name on object");
				continue;
			}

			if (!GameUtils::keyExists(&object, SerializableObject::KeyWidth))
			{
				CCLOG("Missing width on object");
				continue;
			}

			if (!GameUtils::keyExists(&object, SerializableObject::KeyHeight))
			{
				CCLOG("Missing height on object");
				continue;
			}

			if (!GameUtils::keyExists(&object, SerializableObject::KeyXPosition))
			{
				CCLOG("Missing x position on object");
				continue;
			}

			if (!GameUtils::keyExists(&object, SerializableObject::KeyYPosition))
			{
				CCLOG("Missing y position on object");
				continue;
			}

			typeName = object.at(SerializableObject::KeyType).asString();

			// Fire event requesting the deserialization of this object
			DeserializationEvents::TriggerRequestObjectDeserialize(DeserializationEvents::ObjectDeserializationRequestArgs(
				typeName,
				object
			));
		}
	}

	// Stop listening for object deserialization events
	Director::getInstance()->getRunningScene()->getEventDispatcher()->removeCustomEventListeners(DeserializationEvents::ObjectDeserializeEvent);

	SerializableLayer* instance = SerializableLayer::create(&properties, name, deserializedObjects);
}
