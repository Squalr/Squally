#include "DecorDeserializer.h"

SerializableLayer* DecorDeserializer::deserialize(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::deserialize(objectGroup);
	ValueVector objects = objectGroup->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		Sprite* sprite = ObjectDeserializer::loadObject(object);

		layer->addChild(sprite);
	}

	return layer;
}
