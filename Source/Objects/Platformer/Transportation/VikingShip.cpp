#include "VikingShip.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Hackables/HackableCode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"

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

VikingShip::VikingShip(cocos2d::ValueMap& properties) : super(properties, CSize(1083.0f, 931.0f))
{
	this->parseDirection();
	this->mountSpeed = GameUtils::getKeyOrDefault(this->properties, VikingShip::PropertySpeed, Value(512.0f)).asFloat();
	this->ship = SmartAnimationNode::create(ObjectResources::Transportation_VikingShip_Animations);
	this->bottomCollision = CollisionObject::create(
		CollisionObject::createBox(CSize(800.0f, 48.0f)),
		int(PlatformerCollisionType::PassThrough),
		CollisionObject::Properties(false, false)
	);

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

	this->bottomCollision->setPositionY(-420.0f);
}

void VikingShip::initializeListeners()
{
	super::initializeListeners();
	
	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionData collisionData)
	{
		this->reverse();
		this->dismountAll();
		
		return CollisionResult::CollideWithPhysics;
	});
}

void VikingShip::update(float dt)
{
	super::update(dt);

	this->moveMount(dt);
	this->faceEntityTowardsDirection();
	this->ship->setFlippedX(this->mountDirection == MountDirection::Left);
}

void VikingShip::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->faceEntityTowardsDirection();

	this->isMoving = true;
}

void VikingShip::dismount(PlatformerEntity* entity)
{
	super::dismount(entity);
	
	this->isMoving = false;
}

Vec2 VikingShip::getReparentPosition()
{
	return Vec2(0.0f, -224.0f);
}
