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

	// Fire deserialization events for objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			SerializableObject::deserialize(objects[index].asValueMap(), [deserializedObjects](SerializableObject* object) {
				deserializedObjects->push_back(object);
			});
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
