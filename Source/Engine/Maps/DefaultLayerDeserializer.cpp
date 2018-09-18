#include "DefaultLayerDeserializer.h"

void DefaultLayerDeserializer::onDeserializationRequest(LayerDeserializationRequestArgs* args)
{
	std::string name = args->objectGroup->getGroupName();
	ValueVector objects = args->objectGroup->getObjects();
	ValueMap properties = args->objectGroup->getProperties();
	std::vector<SerializableObject*>* deserializedObjects = new std::vector<SerializableObject*>();

	auto onDeserializeCallback = [deserializedObjects](SerializableObject* object) {
		deserializedObjects->push_back(object);
	};

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

			// Ask all deserializers to try to deserialize object
			IObjectDeserializer::ObjectDeserializationRequestArgs objectDeserializeArgs = IObjectDeserializer::ObjectDeserializationRequestArgs(typeName, object, onDeserializeCallback);

			for (auto it = args->objectDeserializers->begin(); it != args->objectDeserializers->end(); it++)
			{
				(*it)->onDeserializationRequest(&objectDeserializeArgs);

				if (objectDeserializeArgs.handled)
				{
					break;
				}
			}
		}
	}

	SerializableLayer* instance = SerializableLayer::create(&properties, name, deserializedObjects);

	args->callback(instance, args->objectGroup->layerIndex);
}
