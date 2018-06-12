#include "SerializableLayer.h"

SerializableLayer::SerializableLayer()
{
}

SerializableLayer::SerializableLayer(std::string name, std::vector<SerializableObject*>* objects, ValueMap properties)
{
	this->layerName = name;
	this->serializableObjects = objects;
	this->layerProperties = properties;

	for (auto it = objects->begin(); it != objects->end(); it++)
	{
		this->addChild(*it);
	}
}

SerializableLayer::~SerializableLayer()
{
}

SerializableLayer* SerializableLayer::deserialize(TMXObjectGroup* objectGroup)
{
	std::string name = objectGroup->getGroupName();
	ValueVector objects = objectGroup->getObjects();
	ValueMap properties = objectGroup->getProperties();
	std::vector<SerializableObject*>* deserializedObjects = new std::vector<SerializableObject*>();

	// Listen for deserialization events. This allows for the engine to not have to worry about knowing every type of serializable object
	EventListenerCustom* deserializationResultListener = EventListenerCustom::create(DeserializationEvents::DeserializeEvent, [deserializedObjects](EventCustom* event) {
		DeserializationEvents::DeserializeArgs* args = static_cast<DeserializationEvents::DeserializeArgs*>(event->getUserData());
		deserializedObjects->push_back(args->serializableObject);

	});
	Director::getInstance()->getRunningScene()->getEventDispatcher()->addEventListenerWithSceneGraphPriority(deserializationResultListener, Director::getInstance()->getRunningScene());

	// Fire deserialization events for objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			SerializableObject::deserialize(objects[index].asValueMap());
		}
	}

	SerializableLayer* instance = new SerializableLayer(name, deserializedObjects, properties);

	instance->autorelease();

	return instance;
}

std::string SerializableLayer::serialize()
{
	std::string prefix = "<objectgroup name=" + StrUtils::quote(this->layerName) + ">";
	std::string suffix = "</objectgroup>";

	std::string content = "";

	for (auto it = this->serializableObjects->begin(); it != this->serializableObjects->end(); it++)
	{
		content += (*it)->serialize();
	}

	return prefix + content + suffix;
}
