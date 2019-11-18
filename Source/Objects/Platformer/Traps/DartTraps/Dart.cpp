#include "Dart.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

Dart* Dart::create(float rotation, float speed, float visualRotation)
{
	Dart* instance = new Dart(rotation, speed, visualRotation);

	instance->autorelease();

	return instance;
}

Dart::Dart(float rotation, float speed, float visualRotation) : super(
	ValueMap(),
	PhysicsBody::createBox(
		Size(64.0f, 16.0f),
		PHYSICSBODY_MATERIAL_DEFAULT,
		Vec2::ZERO
	),
	(int)PlatformerCollisionType::Damage,
	false,
	false
)
{
	this->dartSprite = Sprite::create(ObjectResources::War_Machines_Dartgun_DART);

	this->setRotation(visualRotation);

	float rotationInRad = rotation * float(M_PI) / 180.0f;
	this->setVelocity(Vec2(speed * std::cos(-rotationInRad), speed * std::sin(-rotationInRad)));

	this->addChild(this->dartSprite);
}

Dart::~Dart()
{
}
