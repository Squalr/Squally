#include "PlatformerDecorDeserializer.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/GlobalDirector.h"
#include "Engine/Utils/GameUtils.h"
#include "Objects/Platformer/PlatformerDecorObject.h"
#include "Objects/Platformer/PlatformerObjectDeserializer.h"

using namespace cocos2d;

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
		std::string name = properties.at(SerializableObject::MapKeyName).asString();

		// For decor, simply grab the resource of the same name of the object type
		Sprite* sprite = Sprite::create("Platformer/Decor/" + name + ".png");

		if (sprite == nullptr)
		{
			CCLOG("Non-existant decor");
			return;
		}

		float width = properties.at(SerializableObject::MapKeyWidth).asFloat();
		float height = properties.at(SerializableObject::MapKeyHeight).asFloat();
		float x = properties.at(SerializableObject::MapKeyXPosition).asFloat();
		float y = properties.at(SerializableObject::MapKeyYPosition).asFloat();
		bool repeatX = false;
		bool repeatY = false;
		SerializableObject* newObject = PlatformerDecorObject::create(&properties);

		if (GameUtils::keyExists(&properties, SerializableObject::MapKeyRepeatX))
		{
			repeatX = properties.at(SerializableObject::MapKeyRepeatX).asBool();
		}

		if (GameUtils::keyExists(&properties, SerializableObject::MapKeyRepeatY))
		{
			repeatY = properties.at(SerializableObject::MapKeyRepeatY).asBool();
		}

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

			sprite->getTexture()->setTexParameters(params);
		}
		else
		{
			// Default -- set the scale of the decor based on the height
			newObject->setScale(height / sprite->getContentSize().height);
		}

		newObject->addChild(sprite);

		// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
		sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
		newObject->setPosition(Vec2(x, y + height));

		if (GameUtils::keyExists(&properties, SerializableObject::MapKeyRotation))
		{
			float rotation = properties.at(SerializableObject::MapKeyRotation).asFloat();
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
