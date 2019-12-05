#include "ThrownObject.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Events/CombatEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObjectGenericPreview.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

ThrownObject* ThrownObject::create(PlatformerEntity* caster, std::string objectResource)
{
	ThrownObject* instance = new ThrownObject(caster, objectResource);

	instance->autorelease();

	return instance;
}

ThrownObject::ThrownObject(PlatformerEntity* caster, std::string objectResource)
	: Projectile(caster, CollisionObject::createCapsulePolygon(Size(64.0f, 128.0f)), CombatCollisionType::Projectile, 1.0f, true)
{
	this->objectResource = objectResource;
	this->objectSprite = Sprite::create(objectResource);

	if (caster != nullptr)
	{
		this->objectSprite->setFlippedX(caster->isFlippedX());
	}
	
	this->addChild(this->objectSprite);
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

cocos2d::Vec2 ThrownObject::getButtonOffset()
{
	return Vec2(0.0f, 64.0f);
}

HackablePreview* ThrownObject::createDefaultPreview()
{
	return ThrownObjectGenericPreview::create(this->objectResource);
}

HackablePreview* ThrownObject::createVelocityPreview()
{
	return ThrownObjectGenericPreview::create(this->objectResource);
}

HackablePreview* ThrownObject::createAccelerationPreview()
{
	return ThrownObjectGenericPreview::create(this->objectResource);
}
