#include "IsometricDecorDeserializer.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"

#include "Objects/Isometric/IsometricDecorObject.h"

#include "Engine/Utils/GameUtils.h"

using namespace cocos2d;

const std::string IsometricDecorDeserializer::MapKeyTypeDecor = "decor";

IsometricDecorDeserializer* IsometricDecorDeserializer::create()
{
	IsometricDecorDeserializer* instance = new IsometricDecorDeserializer();

	instance->autorelease();

	return instance;
}

IsometricDecorDeserializer::IsometricDecorDeserializer() : super(IsometricDecorDeserializer::MapKeyTypeDecor)
{
}

IsometricDecorDeserializer::~IsometricDecorDeserializer()
{
}

void IsometricDecorDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	const std::string name = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyName, Value("")).asString();

	// For decor, simply grab the resource of the same name of the object type
	Sprite* sprite = Sprite::create("Private/Isometric/Decor" + name + ".png");

	if (sprite == nullptr)
	{
		CCLOG("Non-existant decor");
		return;
	}

	GameObject* newObject = IsometricDecorObject::create(properties);
	newObject->addChild(sprite);

	newObject->setZSorted(true);

	if (GameUtils::keyExists(properties, "flip-x"))
	{
		bool flipX = properties.at("flip-x").asBool();
		sprite->setFlippedX(flipX);
	}

	if (GameUtils::keyExists(properties, "flip-y"))
	{
		bool flipY = properties.at("flip-y").asBool();
		sprite->setFlippedY(flipY);
	}

	if (GameUtils::keyExists(properties, "float-x"))
	{
		float floatX = properties.at("float-x").asFloat();
		float timeX = 1.0f;

		if (GameUtils::keyExists(properties, "float-time-x"))
		{
			timeX = properties.at("float-time-x").asFloat();
		}

		FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(floatX, 0.0f)));
		FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(-floatX, 0.0f)));

		newObject->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	}

	if (GameUtils::keyExists(properties, "float-y"))
	{
		float floatY = properties.at("float-y").asFloat();
		float timeY = 1.0f;

		if (GameUtils::keyExists(properties, "float-time-y"))
		{
			timeY = properties.at("float-time-y").asFloat();
		}

		FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, floatY)));
		FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, -floatY)));
		newObject->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
	}

	args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newObject));
}
