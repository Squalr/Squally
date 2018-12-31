#include "IsometricDecorDeserializer.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Objects/Isometric/IsometricDecorObject.h"
#include "Objects/Isometric/IsometricObjectDeserializer.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

IsometricDecorDeserializer* IsometricDecorDeserializer::instance = nullptr;
const std::string IsometricDecorDeserializer::KeyTypeDecor = "iso_decor";

void IsometricDecorDeserializer::registerGlobalNode()
{
	if (IsometricDecorDeserializer::instance == nullptr)
	{
		IsometricDecorDeserializer::instance = new IsometricDecorDeserializer();

		instance->autorelease();

		// Register this class globally so that it can always listen for events
		GlobalDirector::getInstance()->registerGlobalNode(IsometricDecorDeserializer::instance);
	}
}

void IsometricDecorDeserializer::initializeListeners()
{
	super::initializeListeners();

	EventListenerCustom* deserializationRequestListener = EventListenerCustom::create(
		DeserializationEvents::RequestObjectDeserializeEvent,
		[=](EventCustom* args) { this->onDeserializationRequest((DeserializationEvents::ObjectDeserializationRequestArgs*)args->getUserData()); }
	);

	this->addEventListener(deserializationRequestListener);
}

void IsometricDecorDeserializer::onDeserializationRequest(DeserializationEvents::ObjectDeserializationRequestArgs* args)
{
	if (args->typeName == IsometricDecorDeserializer::KeyTypeDecor)
	{
		ValueMap properties = args->properties;
		std::string name = properties.at(SerializableObject::MapKeyName).asString();

		// For decor, simply grab the resource of the same name of the object type
		Sprite* sprite = Sprite::create("Gameplay/Isometric/Decor" + name + ".png");

		if (sprite == nullptr)
		{
			CCLOG("Non-existant decor");
			return;
		}

		SerializableObject* newObject = IsometricDecorObject::create(&properties);
		newObject->addChild(sprite);

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
