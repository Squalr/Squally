#include "ParallaxParser.h"

SerializableLayer* ParallaxParser::parse(TMXObjectGroup* objectGroup)
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

		if (!GameUtils::keyExists(object, "speed-x") && !GameUtils::keyExists(object, "speed-y"))
		{
			CCLOG("Missing speed propertie(s) on parallax object");
			continue;
		}

		float speedX = object.at("speed-x").asFloat();
		float speedY = object.at("speed-y").asFloat();

		Sprite* sprite = ObjectParser::loadObject(object);
		Vec2 position = sprite->getPosition();
		Node *node = Node::create();

		sprite->setPosition(Vec2::ZERO);
		node->addChild(sprite);

		ParallaxObject* parallaxObject = ParallaxObject::create(node, position, Vec2(speedX, speedY));

		layer->addChild(parallaxObject);
	}

	return layer;
}
