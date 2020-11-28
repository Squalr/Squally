#include "PlatformerDecorObject.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCValue.h"
#include "cocos/renderer/CCTextureCache.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Optimization/LazyNode.h"
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
	const std::string name = this->properties.at(GameObject::MapKeyName).asString();
	this->filePath = "Private/Platformer/Decor/" + name + ".png";
	this->sprite = LazyNode<Sprite>::create(CC_CALLBACK_0(PlatformerDecorObject::buildSprite, this));
	this->objectSize = Size(
		 GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	);
	this->enableHackerModeEvents = true;

    Director::getInstance()->getTextureCache()->cacheImageAsync(this->filePath);

	// Makes getScreenBounds() work
	this->setContentSize(this->objectSize);

	this->addChild(this->sprite);
}

PlatformerDecorObject::~PlatformerDecorObject()
{
}

void PlatformerDecorObject::onEnter()
{
	super::onEnter();

	this->runBounce();
	this->scheduleUpdate();
	this->optimizationHideOffscreenDecor();
}

void PlatformerDecorObject::update(float dt)
{
	super::update(dt);

	this->optimizationHideOffscreenDecor();
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

void PlatformerDecorObject::optimizationHideOffscreenDecor()
{
	static const Size Padding = Size(0.0f, 0.0f);
	static const Rect CameraRect = Rect(Vec2::ZERO, Director::getInstance()->getVisibleSize());
	Rect thisRect = GameUtils::getScreenBounds(this, Padding);

	if (CameraRect.intersectsRect(thisRect))
	{
		this->sprite->lazyGet()->setVisible(true);
	}
	else if (this->sprite->isBuilt())
	{
		this->sprite->lazyGet()->setVisible(false);
	}
}

Sprite* PlatformerDecorObject::buildSprite()
{
	// For decor, simply grab the resource of the same name of the object type
	Sprite* instance = Sprite::create(this->filePath);

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
			instance->setTextureRect(Rect(0.0f, 0.0f, this->objectSize.width, instance->getContentSize().height));

			// X is repeating -- set the scale based on the height
			instance->setScale(this->objectSize.height / instance->getContentSize().height);
		}
		if (repeatY && !repeatX)
		{
			instance->setTextureRect(Rect(0.0f, 0.0f, instance->getContentSize().width, this->objectSize.height));

			// Y is repeating -- set the scale based on the width
			instance->setScale(this->objectSize.width / instance->getContentSize().width);
		}
		else if (repeatX && repeatY)
		{
			instance->setTextureRect(Rect(0.0f, 0.0f, this->objectSize.width, this->objectSize.height));
		}

		Texture2D* texture = instance->getTexture();

		if (texture != nullptr)
		{
			texture->setTexParameters(params);
		}
	}
	else
	{
		// Default -- set the scale of the decor based on the height
		instance->setScale(this->objectSize.height / instance->getContentSize().height);
	}
	
	if (GameUtils::keyExists(this->properties, GameObject::MapKeyAutoScale))
	{
		instance->setScale(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyAutoScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(this->properties, GameObject::MapKeyScale))
	{
		instance->setScale(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyScale, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(this->properties, GameObject::MapKeyScaleX))
	{
		instance->setScaleX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyScaleX, Value(1.0f)).asFloat());
	}
	
	if (GameUtils::keyExists(this->properties, GameObject::MapKeyScaleY))
	{
		instance->setScaleY(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyScaleY, Value(1.0f)).asFloat());
	}
	
	// TMX tile maps rotate around a different anchor point than cocos2d-x by default, so we have to account for this
	instance->setAnchorPoint(Vec2(0.0f, 1.0f));
	instance->setPosition(Vec2(-this->objectSize.width / 2.0f, this->objectSize.height / 2.0f));

	if (GameUtils::keyExists(this->properties, GameObject::MapKeyRotation))
	{
		float rotation = this->properties.at(GameObject::MapKeyRotation).asFloat();
		instance->setRotation(rotation);
	}

	if (GameUtils::keyExists(this->properties, "flip-x"))
	{
		bool flipX = this->properties.at("flip-x").asBool();
		instance->setFlippedX(flipX);
	}

	if (GameUtils::keyExists(this->properties, "flip-y"))
	{
		bool flipY = this->properties.at("flip-y").asBool();
		instance->setFlippedY(flipY);
	}

	return instance;
}
