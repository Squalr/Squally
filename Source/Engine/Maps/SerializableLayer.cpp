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

SerializableLayer* SerializableLayer::deserialize(TMXObjectGroup* objectGroup, std::vector<IDeserializer*>* deserializers)
{
	std::string name = objectGroup->getGroupName();
	ValueVector objects = objectGroup->getObjects();
	ValueMap properties = objectGroup->getProperties();
	std::vector<SerializableObject*>* deserializedObjects = new std::vector<SerializableObject*>();

	auto onDeserializeCallback = [deserializedObjects](SerializableObject* object) {
		deserializedObjects->push_back(object);
	};

	// Fire deserialization events for objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() == cocos2d::Value::Type::MAP)
		{
			ValueMap object = objects[index].asValueMap();
			std::string typeName = "";

			if (!GameUtils::keyExists(object, SerializableObject::KeyType))
			{
				CCLOG("Missing type on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::KeyName))
			{
				CCLOG("Missing name on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::KeyWidth))
			{
				CCLOG("Missing width on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::KeyHeight))
			{
				CCLOG("Missing height on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::KeyXPosition))
			{
				CCLOG("Missing x position on object");
				continue;
			}

			if (!GameUtils::keyExists(object, SerializableObject::KeyYPosition))
			{
				CCLOG("Missing y position on object");
				continue;
			}

			typeName = object.at(SerializableObject::KeyType).asString();

			// Ask all deserializers to try to deserialize object
			IDeserializer::DeserializationRequestArgs args = IDeserializer::DeserializationRequestArgs(typeName, object, onDeserializeCallback);

			for (auto it = deserializers->begin(); it != deserializers->end(); it++)
			{
				(*it)->onDeserializationRequest(&args);
			}
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
