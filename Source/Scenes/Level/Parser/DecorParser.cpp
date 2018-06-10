#include "DecorParser.h"

SerializableLayer* DecorParser::parse(TMXObjectGroup* objectGroup)
{
	SerializableLayer* layer = SerializableLayer::create("");
	ValueVector objects = objectGroup->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		Sprite* sprite = ObjectParser::loadObject(object);

		layer->addChild(sprite);
	}

	return layer;
}
