#include "VikingShip.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string VikingShip::MapKey = "viking-ship";

VikingShip* VikingShip::create(cocos2d::ValueMap& properties)
{
	VikingShip* instance = new VikingShip(properties);

	instance->autorelease();

	return instance;
}

VikingShip::VikingShip(cocos2d::ValueMap& properties) : super(properties, CSize(240.0f, 184.0f))
{
	this->parseDirection();
	this->mountSpeed = GameUtils::getKeyOrDefault(this->properties, VikingShip::PropertySpeed, Value(0.0f)).asFloat();
	this->ship = SmartAnimationNode::create(ObjectResources::Transportation_VikingShip_Animations);

	this->frontNode->addChild(this->bottomCollision);
	this->frontNode->addChild(this->ship);
}

VikingShip::~VikingShip()
{
}

void VikingShip::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void VikingShip::initializePositions()
{
	super::initializePositions();

	this->bottomCollision->setPositionY(-108.0f);
}

void VikingShip::initializeListeners()
{
	super::initializeListeners();
	

	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionData collisionData)
	{
		this->reverse();
		this->dismount();
		
		return CollisionResult::CollideWithPhysics;
	});
}

void VikingShip::update(float dt)
{
	super::update(dt);

	this->moveMount(dt);
	this->faceEntityTowardsDirection();
}

void VikingShip::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->faceEntityTowardsDirection();

	this->isMoving = true;
}

void VikingShip::dismount()
{
	super::dismount();
	
	this->isMoving = false;
}

Vec2 VikingShip::getReparentPosition()
{
	return Vec2(0.0f, 128.0f);
}
