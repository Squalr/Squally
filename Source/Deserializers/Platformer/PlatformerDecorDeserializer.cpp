#include "PlatformerDecorDeserializer.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/LogUtils.h"
#include "Engine/Utils/GameUtils.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Objects/Platformer/PlatformerDecorObject.h"

using namespace cocos2d;

const std::string PlatformerDecorDeserializer::MapKeyTypeDecor = "decor";

PlatformerDecorDeserializer* PlatformerDecorDeserializer::create()
{
	PlatformerDecorDeserializer* instance = new PlatformerDecorDeserializer();

	instance->autorelease();

	return instance;
}

PlatformerDecorDeserializer::PlatformerDecorDeserializer() : super(PlatformerDecorDeserializer::MapKeyTypeDecor, { (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() })
{
}

PlatformerDecorDeserializer::~PlatformerDecorDeserializer()
{
}

void PlatformerDecorDeserializer::deserialize(ObjectDeserializer::ObjectDeserializationRequestArgs* args)
{
	ValueMap properties = args->properties;
	std::string name = properties.at(GameObject::MapKeyName).asString();

	// For decor, simply grab the resource of the same name of the object type
	const std::string path = "Private/Platformer/Decor/" + name + ".png";
	Sprite* sprite = Sprite::create(path);

	if (sprite == nullptr)
	{
		LogUtils::logError("Non-existant decor" + path);
		return;
	}

	float width = properties.at(GameObject::MapKeyWidth).asFloat();
	float height = properties.at(GameObject::MapKeyHeight).asFloat();
	float x = properties.at(GameObject::MapKeyXPosition).asFloat();
	float y = properties.at(GameObject::MapKeyYPosition).asFloat();
	bool repeatX = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyRepeatX, Value(false)).asBool();
	bool repeatY = GameUtils::getKeyOrDefault(properties, GameObject::MapKeyRepeatY, Value(false)).asBool();
	GameObject* newObject = PlatformerDecorObject::create(properties);

	if (repeatX || repeatY)
	{
		Texture2D::TexParams params = Texture2D::TexParams();
		params.minFilter = GL_LINEAR;
		params.magFilter = GL_LINEAR;

		if (repeatX)
		{
			params.wrapS = GL_REPEAT;
		}
		
		if (repeatY)
		{
			params.wrapT = GL_REPEAT;
		}

		if (repeatX && !repeatY)
		{
			sprite->setTextureRect(Rect(0.0f, 0.0f, width, sprite->getContentSize().height));

			// X is repeating -- set the scale based on the height
			newObject->setScale(height / sprite->getContentSize().height);
		}
		if (repeatY && !repeatX)
		{
			sprite->setTextureRect(Rect(0.0f, 0.0f, sprite->getContentSize().width, height));

			// Y is repeating -- set the scale based on the width
			newObject->setScale(width / sprite->getContentSize().width);
		}
		else if (repeatX && repeatY)
		{
			sprite->setTextureRect(Rect(0.0f, 0.0f, width, height));
		}

		Texture2D* texture = sprite->getTexture();

		if (texture != nullptr)
		{
			texture->setTexParameters(params);
		}
	}
	else
	{
		// Default -- set the scale of the decor based on the height
		newObject->setScale(height / sprite->getContentSize().height);
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyAutoScale))
	{
		newObject->setScale(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAutoScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScale))
	{
		newObject->setScale(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScaleX))
	{
		newObject->setScaleX(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScaleX, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScaleY))
	{
		newObject->setScaleY(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScaleY, Value(1.0f)).asFloat());
	}

	newObject->addChild(sprite);

	// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
	sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	newObject->setPosition(Vec2(x, y + height));

	newObject->setPositionZ(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyDepth, Value(0.0f)).asFloat());

	if (GameUtils::keyExists(properties, GameObject::MapKeyRotation))
	{
		float rotation = properties.at(GameObject::MapKeyRotation).asFloat();
		newObject->setRotation(rotation);
	}

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

	this->deserializeProperties(newObject, properties);

	args->onDeserializeCallback(ObjectDeserializer::ObjectDeserializationArgs(newObject));
}
