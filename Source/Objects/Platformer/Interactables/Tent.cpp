#include "Tent.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/ObjectEvents.h"
#include "Engine/Localization/LocalizedString.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Hackables/HackableData.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/SwitchEvents.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Tent::MapKeyTent = "tent";

Tent* Tent::create(ValueMap& initProperties)
{
	Tent* instance = new Tent(initProperties);

	instance->autorelease();

	return instance;
}

Tent::Tent(ValueMap& initProperties) : HackableObject(initProperties)
{
	this->tentBack = Sprite::create(ObjectResources::Interactive_TentBack);
	this->tentFront = Sprite::create(ObjectResources::Interactive_TentFront);
	this->topCollision = CollisionObject::create(PhysicsBody::createBox(Size(224.0f, 48.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);
	this->healCollision = CollisionObject::create(PhysicsBody::createBox(Size(224.0f, 48.0f)), (CollisionType)PlatformerCollisionType::Solid, false, false);

	this->addChild(this->healCollision);
	this->addChild(this->topCollision);
	this->addChild(this->tentBack);
	this->addChild(this->tentFront);
}

Tent::~Tent()
{
}

void Tent::onEnter()
{
	super::onEnter();

	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->tentFront));

	this->scheduleUpdate();
}

void Tent::initializePositions()
{
	super::initializePositions();

	this->topCollision->setPosition(Vec2(0.0f, 320.0f));
}

void Tent::initializeListeners()
{
	super::initializeListeners();

	this->topCollision->whenCollidesWith({(int)PlatformerCollisionType::Force, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics}, [=](CollisionObject::CollisionData data)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}
