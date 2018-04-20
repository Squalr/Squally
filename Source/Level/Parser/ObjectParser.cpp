#include "ObjectParser.h"

Layer* ObjectParser::parse(TMXObjectGroup* objectGroup)
{
	Layer* layer = Layer::create();
	ValueVector objects = objectGroup->getObjects();

	// Create objects
	for (int index = 0; index < size(objects); index++)
	{
		if (objects[index].getType() != cocos2d::Value::Type::MAP)
		{
			continue;
		}

		ValueMap object = objects[index].asValueMap();
		std::string type = object.at("type").asString();

		HackableObject* newObject = nullptr;

		if (type == "warp-gate")
		{
			newObject = WarpGate::create();
		}
		else if (type == "warp-gate-exact-scan-1")
		{
			newObject = WarpGateExactScanTutorial::create();
		}
		else if (type == "plushie_monkey")
		{
			newObject = PlushieMonkey::create();
		}
		else if (type == "monitor")
		{
			string dialog = object.at("dialog").asString();

			newObject = Monitor::create("Dialog\\" + dialog + ".json");
		}
		else
		{
			throw std::invalid_argument("Invalid object");
		}

		newObject->setPosition(Vec2(object.at("x").asFloat() + object.at("width").asFloat() / 2, object.at("y").asFloat() + object.at("height").asFloat() / 2));
		layer->addChild(newObject);
	}

	return layer;
}

Sprite* ObjectParser::loadObject(ValueMap object)
{
	std::string type = object.at("type").asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* newObject = Sprite::create("Decor/" + type + ".png");

	if (newObject == nullptr)
	{
		throw std::invalid_argument("Non-existant decor");
	}

	float width = object.at("width").asFloat();
	float height = object.at("height").asFloat();
	float x = object.at("x").asFloat() + width / 2.0f;
	float y = object.at("y").asFloat() + height / 2.0f;

	// Scale decor based on rectangle size (only using height for simplicity)
	newObject->setScale(height / newObject->getContentSize().height);

	// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
	newObject->setAnchorPoint(Vec2(0.0f, 1.0f));
	newObject->setPosition(Vec2(x - width / 2.0f, y + height / 2.0f));

	if (GameUtils::keyExists(object, "rotation"))
	{
		float rotation = object.at("rotation").asFloat();
		newObject->setRotation(rotation);
	}

	if (GameUtils::keyExists(object, "flip-x"))
	{
		bool flipX = object.at("flip-x").asBool();
		newObject->setFlippedX(flipX);
	}

	if (GameUtils::keyExists(object, "flip-y"))
	{
		bool flipY = object.at("flip-y").asBool();
		newObject->setFlippedY(flipY);
	}

	if (GameUtils::keyExists(object, "float-x"))
	{
		float floatX = object.at("float-x").asFloat();
		float timeX = 1.0f;

		if (GameUtils::keyExists(object, "float-time-x"))
		{
			timeX = object.at("float-time-x").asFloat();
		}

		FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(floatX, 0.0f)));
		FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(-floatX, 0.0f)));

		newObject->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	}

	if (GameUtils::keyExists(object, "float-y"))
	{
		float floatY = object.at("float-y").asFloat();
		float timeY = 1.0f;

		if (GameUtils::keyExists(object, "float-time-y"))
		{
			timeY = object.at("float-time-y").asFloat();
		}

		FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, floatY)));
		FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, -floatY)));
		newObject->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
	}

	return newObject;
}
