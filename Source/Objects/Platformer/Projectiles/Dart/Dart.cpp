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

Dart::Dart(float dartRotation, float dartSpeed) : super(nullptr, CollisionObject::createBox(Size(64.0f, 16.0f)), (int)PlatformerCollisionType::Damage, false)
{
	this->dartSpeed = dartSpeed;
	this->sprite = Sprite::create(ObjectResources::Traps_DartTripodLauncher_DART);

	this->sprite->setRotation(270.0f);
	this->setProjectileRotation(dartRotation);

	this->contentNode->addChild(this->sprite);
}

Dart::~Dart()
{
}

void Dart::onEnter()
{
	super::onEnter();
	
	this->getCollision()->setVelocity(Vec2(this->dartSpeed, this->dartSpeed));
}
