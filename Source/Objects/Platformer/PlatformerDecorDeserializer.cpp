#include "PlatformerDecorDeserializer.h"

PlatformerDecorDeserializer* PlatformerDecorDeserializer::instance = nullptr;
const std::string PlatformerDecorDeserializer::KeyTypeDecor = "decor";

void PlatformerDecorDeserializer::registerGlobalNode()
{
	if (PlatformerDecorDeserializer::instance == nullptr)
	{
		PlatformerDecorDeserializer::instance = new PlatformerDecorDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(PlatformerDecorDeserializer::instance);
	}
}

void PlatformerDecorDeserializer::initializeListeners()
{
	GlobalNode::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void PlatformerDecorDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == PlatformerDecorDeserializer::KeyTypeDecor)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::KeyName).asString();

		// For decor, simply grab the resource of the same name of the object type
		Sprite* sprite = Sprite::create("GamePlay/Platformer/Decor/" + name + ".png");

		if (sprite == nullptr)
		{
			CCLOG("Non-existant decor");
			return;
		}

		float width = properties.at(SerializableObject::KeyWidth).asFloat();
		float height = properties.at(SerializableObject::KeyHeight).asFloat();
		float x = properties.at(SerializableObject::KeyXPosition).asFloat();
		float y = properties.at(SerializableObject::KeyYPosition).asFloat();
		SerializableObject* newObject = PlatformerDecorObject::create(&properties);

		newObject->addChild(sprite);

		// Scale decor based on rectangle size (only using height for simplicity)
		newObject->setScale(height / sprite->getContentSize().height);

		// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
		sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
		newObject->setPosition(Vec2(x, y + height));

		if (GameUtils::keyExists(&properties, SerializableObject::KeyRotation))
		{
			float rotation = properties.at(SerializableObject::KeyRotation).asFloat();
			newObject->setRotation(rotation);
		}

		if (GameUtils::keyExists(&properties, "flip-x"))
		{
			bool flipX = properties.at("flip-x").asBool();
			sprite->setFlippedX(flipX);
		}

		if (GameUtils::keyExists(&properties, "flip-y"))
		{
			bool flipY = properties.at("flip-y").asBool();
			sprite->setFlippedY(flipY);
		}

		if (GameUtils::keyExists(&properties, "float-x"))
		{
			float floatX = properties.at("float-x").asFloat();
			float timeX = 1.0f;

			if (GameUtils::keyExists(&properties, "float-time-x"))
			{
				timeX = properties.at("float-time-x").asFloat();
			}

			FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(floatX, 0.0f)));
			FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(-floatX, 0.0f)));

			newObject->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
		}

		if (GameUtils::keyExists(&properties, "float-y"))
		{
			float floatY = properties.at("float-y").asFloat();
			float timeY = 1.0f;

			if (GameUtils::keyExists(&properties, "float-time-y"))
			{
				timeY = properties.at("float-time-y").asFloat();
			}

			FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, floatY)));
			FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, -floatY)));
			newObject->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
		}

		args->onDeserializeCallback(DeserializationEvents::ObjectDeserializationArgs(newObject));
	}
}
