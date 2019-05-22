#include "Tent.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"

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

Tent::Tent(ValueMap& initProperties) : super(initProperties)
{
	this->tentBack = Sprite::create(ObjectResources::Interactive_TentBack);
	this->tentFront = Sprite::create(ObjectResources::Interactive_TentFront);
	this->topCollision = CollisionObject::create(this->createTentTopCollision(), (CollisionType)PlatformerCollisionType::Solid, false, false);
	this->healCollision = CollisionObject::create(PhysicsBody::createBox(Size(356.0f, 356.0f)), (CollisionType)PlatformerCollisionType::Trigger, false, false);

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

	this->scheduleUpdate();
}

void Tent::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	ObjectEvents::TriggerElevateObject(ObjectEvents::RelocateObjectArgs(this->tentFront));
}

void Tent::initializePositions()
{
	super::initializePositions();

	this->tentBack->setPosition(Vec2(-132.0f, -140.0f));
	this->healCollision->setPosition(Vec2(0.0f, -160.0f));
	this->topCollision->setPosition(Vec2(-8.0f, 320.0f));
}

void Tent::initializeListeners()
{
	super::initializeListeners();

	this->topCollision->whenCollidesWith({(int)PlatformerCollisionType::Force, (int)PlatformerCollisionType::Player, (int)PlatformerCollisionType::Physics}, [=](CollisionObject::CollisionData data)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}


PhysicsBody* Tent::createTentTopCollision()
{
	std::vector<Vec2> points = std::vector<Vec2>();

	points.push_back(Vec2(0.0f, 0.0f));
	points.push_back(Vec2(-336.0f, -192.0f));
	points.push_back(Vec2(0.0f, -256.0f));
	points.push_back(Vec2(336.0f, -192.0f));

	PhysicsBody* physicsBody = PhysicsBody::createPolygon(points.data(), points.size());

	return physicsBody;
}

