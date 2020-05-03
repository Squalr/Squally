#include "PlatformerDecorObject.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/LogUtils.h"

using namespace cocos2d;

PlatformerDecorObject* PlatformerDecorObject::create(ValueMap& properties)
{
	PlatformerDecorObject* instance = new PlatformerDecorObject(properties);

	instance->autorelease();

	return instance;
}

PlatformerDecorObject::PlatformerDecorObject(ValueMap& properties) : super(properties)
{
	this->cachedDepth = 0.0f;

	std::string name = this->properties.at(GameObject::MapKeyName).asString();

	// For decor, simply grab the resource of the same name of the object type
	this->sprite = Sprite::create("Private/Platformer/Decor/" + name + ".png");

	float width = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat();
	float height = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();
	float x = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyXPosition, Value(0.0f)).asFloat();
	float y = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyYPosition, Value(0.0f)).asFloat();
	bool repeatX = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyRepeatX, Value(false)).asBool();
	bool repeatY = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyRepeatY, Value(false)).asBool();

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
			this->setScale(height / sprite->getContentSize().height);
		}
		if (repeatY && !repeatX)
		{
			sprite->setTextureRect(Rect(0.0f, 0.0f, sprite->getContentSize().width, height));

			// Y is repeating -- set the scale based on the width
			this->setScale(width / sprite->getContentSize().width);
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
		this->setScale(height / sprite->getContentSize().height);
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyAutoScale))
	{
		this->setScale(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyAutoScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScale))
	{
		this->setScale(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScaleX))
	{
		this->setScaleX(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScaleX, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(properties, GameObject::MapKeyScaleY))
	{
		this->setScaleY(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyScaleY, Value(1.0f)).asFloat());
	}

	// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
	sprite->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->setPosition(Vec2(x, y + height));

	this->setPositionZ(GameUtils::getKeyOrDefault(properties, GameObject::MapKeyDepth, Value(0.0f)).asFloat());

	if (GameUtils::keyExists(properties, GameObject::MapKeyRotation))
	{
		float rotation = properties.at(GameObject::MapKeyRotation).asFloat();
		this->setRotation(rotation);
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

	this->addChild(sprite);
}

PlatformerDecorObject::~PlatformerDecorObject()
{
}

void PlatformerDecorObject::onEnter()
{
	super::onEnter();

	this->runBounce();

	this->cachedDepth = GameUtils::getDepth(this);
}

void PlatformerDecorObject::onHackerModeEnable()
{
	super::onHackerModeEnable();

	this->setVisible(false);
}

void PlatformerDecorObject::onHackerModeDisable()
{
	super::onHackerModeDisable();

	this->setVisible(true);
}

void PlatformerDecorObject::update(float dt)
{
	super::update(dt);

	const float Increment = 64.0f;
	const float HalfIncrement = Increment / 2.0f;

	if (this->cachedDepth >= (GameCamera::getInstance()->getTargetDepth() + Increment * 6 + HalfIncrement))
	{
		this->sprite->setOpacity(64);
	}
	else if (this->cachedDepth >= (GameCamera::getInstance()->getTargetDepth() + HalfIncrement))
	{
		this->sprite->setOpacity(127);
	}
	else
	{
		this->sprite->setOpacity(255);
	}
}

void PlatformerDecorObject::runBounce()
{
	if (GameUtils::keyExists(this->properties, "float-x"))
	{
		float floatX = this->properties.at("float-x").asFloat();
		float timeX = 1.0f;

		if (GameUtils::keyExists(this->properties, "float-time-x"))
		{
			timeX = this->properties.at("float-time-x").asFloat();
		}

		FiniteTimeAction* bounceX1 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(floatX, 0.0f)));
		FiniteTimeAction* bounceX2 = EaseSineInOut::create(MoveBy::create(timeX, Vec2(-floatX, 0.0f)));

		this->runAction(RepeatForever::create(Sequence::create(bounceX1, bounceX2, nullptr)));
	}

	if (GameUtils::keyExists(this->properties, "float-y"))
	{
		float floatY = this->properties.at("float-y").asFloat();
		float timeY = 1.0f;

		if (GameUtils::keyExists(this->properties, "float-time-y"))
		{
			timeY = this->properties.at("float-time-y").asFloat();
		}

		FiniteTimeAction* bounceY1 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, floatY)));
		FiniteTimeAction* bounceY2 = EaseSineInOut::create(MoveBy::create(timeY, Vec2(0.0f, -floatY)));
		this->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));
	}
}
