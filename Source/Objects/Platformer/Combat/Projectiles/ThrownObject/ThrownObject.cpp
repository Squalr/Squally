#include "ThrownObject.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObjectGenericPreview.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

ThrownObject* ThrownObject::create(PlatformerEntity* caster, std::string objectResource, cocos2d::Size collisionSize)
{
	return ThrownObject::create(caster, Sprite::create(objectResource), collisionSize);
}

ThrownObject* ThrownObject::create(PlatformerEntity* caster, cocos2d::Node* object, cocos2d::Size collisionSize)
{
	ThrownObject* instance = new ThrownObject(caster, object, collisionSize);

	instance->autorelease();

	return instance;
}

ThrownObject::ThrownObject(PlatformerEntity* caster, cocos2d::Node* object, cocos2d::Size collisionSize)
	: super(caster, CollisionObject::createCapsulePolygon(collisionSize), CombatCollisionType::Projectile, 1.0f, true)
{
	this->object = object;

	if (caster != nullptr)
	{
		this->setFlippedX(caster->isFlippedX());
		this->setFlippedY(caster->isFlippedY());
	}
	
	this->addChild(this->object);
}

ThrownObject::~ThrownObject()
{
}

void ThrownObject::onEnter()
{
	super::onEnter();
}

void ThrownObject::initializePositions()
{
	super::initializePositions();
}

void ThrownObject::setFlippedX(bool isFlipped)
{
	if (dynamic_cast<Sprite*>(this->object) != nullptr)
	{
		dynamic_cast<Sprite*>(this->object)->setFlippedX(isFlipped);
	}
	else if (dynamic_cast<SmartAnimationNode*>(this->object) != nullptr)
	{
		dynamic_cast<SmartAnimationNode*>(this->object)->setFlippedX(isFlipped);
	}
	else if (dynamic_cast<SmartAnimationSequenceNode*>(this->object) != nullptr)
	{
		dynamic_cast<SmartAnimationSequenceNode*>(this->object)->setFlippedX(isFlipped);
	}
}

void ThrownObject::setFlippedY(bool isFlipped)
{
	if (dynamic_cast<Sprite*>(this->object) != nullptr)
	{
		dynamic_cast<Sprite*>(this->object)->setFlippedY(isFlipped);
	}
	else if (dynamic_cast<SmartAnimationNode*>(this->object) != nullptr)
	{
		dynamic_cast<SmartAnimationNode*>(this->object)->setFlippedY(isFlipped);
	}
	else if (dynamic_cast<SmartAnimationSequenceNode*>(this->object) != nullptr)
	{
		dynamic_cast<SmartAnimationSequenceNode*>(this->object)->setFlippedY(isFlipped);
	}
}

cocos2d::Vec2 ThrownObject::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ThrownObject::createDefaultPreview()
{
	return ThrownObjectGenericPreview::create(this->object);
}

HackablePreview* ThrownObject::createVelocityPreview()
{
	return ThrownObjectGenericPreview::create(this->object);
}

HackablePreview* ThrownObject::createAccelerationPreview()
{
	return ThrownObjectGenericPreview::create(this->object);
}
