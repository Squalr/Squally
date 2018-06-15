#include "DecorDeserializer.h"

const std::string DecorDeserializer::KeyTypeDecor = "decor";

void DecorDeserializer::onDeserializationRequest(DeserializationRequestArgs* args)
{
	if (args->typeName == DecorDeserializer::KeyTypeDecor)
	{
		ValueMap object = args->valueMap;
		std::string name = object.at(SerializableObject::KeyName).asString();

		// For decor, simply grab the resource of the same name of the object type
		Sprite* sprite = Sprite::create("Decor/" + name + ".png");

		if (sprite == nullptr)
		{
			CCLOG("Non-existant decor");
			return;
		}

		float width = object.at(SerializableObject::KeyWidth).asFloat();
		float height = object.at(SerializableObject::KeyHeight).asFloat();
		float x = object.at(SerializableObject::KeyXPosition).asFloat() + width / 2.0f;
		float y = object.at(SerializableObject::KeyYPosition).asFloat() + height / 2.0f;
		SerializableObject* newObject = nullptr;
		
		if (GameUtils::keyExists(object, "isParallax"))
		{
			bool isParallax = object.at("isParallax").asBool();

			if (isParallax)
			{
				Vec2 parallaxSpeed = Vec2::ZERO;

				if (GameUtils::keyExists(object, "parallax-speed-x"))
				{
					parallaxSpeed.x = object.at("parallax-speed-x").asFloat();
				}

				if (GameUtils::keyExists(object, "parallax-speed-y"))
				{
					parallaxSpeed.y = object.at("parallax-speed-y").asFloat();
				}

				newObject = ParallaxObject::create(sprite, parallaxSpeed);
			}
		}
		
		if (newObject == nullptr)
		{
			newObject = DecorObject::create();
			newObject->addChild(sprite);
		}

		// Scale decor based on rectangle size (only using height for simplicity)
		newObject->setScale(height / sprite->getContentSize().height);

		// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
		sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
		newObject->setPosition(Vec2(x - width / 2.0f, y + height / 2.0f));

		if (GameUtils::keyExists(object, SerializableObject::KeyRotation))
		{
			float rotation = object.at(SerializableObject::KeyRotation).asFloat();
			newObject->setRotation(rotation);
		}

		if (GameUtils::keyExists(object, "flip-x"))
		{
			bool flipX = object.at("flip-x").asBool();
			sprite->setFlippedX(flipX);
		}

		if (GameUtils::keyExists(object, "flip-y"))
		{
			bool flipY = object.at("flip-y").asBool();
			sprite->setFlippedY(flipY);
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

		args->callback(newObject);
	}
}