#include "Dart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Dart* Dart::create(float dartRotation, float dartSpeed)
{
	Dart* instance = new Dart(dartRotation, dartSpeed);

	instance->autorelease();

	return instance;
}

Dart::Dart(float dartRotation, float dartSpeed) : super(nullptr, nullptr, CombatCollisionType::Projectile, false)
{
	this->dartRotation = dartRotation;
	this->dartSpeed = dartSpeed;
	this->dartSprite = Sprite::create(ObjectResources::Traps_DartTripodLauncher_DART);
	this->collision = CollisionObject::create(
		ValueMap(),
		PhysicsBody::createBox(
			Size(16.0f, 64.0f),
			PHYSICSBODY_MATERIAL_DEFAULT,
			Vec2::ZERO
		),
		(int)PlatformerCollisionType::Damage,
		false,
		false
	);

	this->collision->addChild(this->dartSprite);
	this->addChild(this->collision);
}

Dart::~Dart()
{
}

void Dart::onEnter()
{
	super::onEnter();

	float rotationInRad = this->dartRotation * float(M_PI) / 180.0f;
	this->collision->setVelocity(Vec2(this->dartSpeed * std::cos(-rotationInRad), this->dartSpeed * std::sin(-rotationInRad)));

	this->dartSprite->setRotation(90.0f);
}

void Dart::reset()
{
	this->collision->setPosition(Vec2::ZERO);
	this->enable();
}

void Dart::disable()
{
	this->collision->setPhysicsEnabled(false);
}

void Dart::enable()
{
	this->collision->setPhysicsEnabled(true);
}
