#include "BreakableCage.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/Sound.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/FXResources.h"

using namespace cocos2d;

const std::string BreakableCage::MapKeyBreakableCage = "breakable-cage";

BreakableCage* BreakableCage::create(ValueMap& initProperties)
{
	BreakableCage* instance = new BreakableCage(initProperties);

	instance->autorelease();

	return instance;
}

BreakableCage::BreakableCage(ValueMap& initProperties, int requiredHits) : super(initProperties, Size(196.0f, 112.0f), requiredHits)
{
	this->cageBottom = CollisionObject::create(PhysicsBody::createBox(Size(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->contentNode = Node::create();
	this->cage = CollisionObject::create(PhysicsBody::createBox(Size(160.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->cageTop = CollisionObject::create(PhysicsBody::createBox(Size(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, true, true);
	this->explosion = SmartAnimationSequenceNode::create();

	this->cageBottom->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageBottom));
	this->cage->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageSide));
	this->cageTop->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageTop));

	this->cageBottom->setPhysicsEnabled(false);
	this->cage->setPhysicsEnabled(false);
	this->cageTop->setPhysicsEnabled(false);

	this->addChild(this->cageBottom);
	this->addChild(this->contentNode);
	this->addChild(this->cage);
	this->addChild(this->cageTop);
	this->addChild(this->explosion);
}

BreakableCage::~BreakableCage()
{
}

void BreakableCage::initializePositions()
{
	super::initializePositions();

	this->cageBottom->setPosition(Vec2(0.0f, -48.0f));
	this->contentNode->setPosition(Vec2(0.0f, 0.0f));
	this->cage->setPosition(Vec2(0.0f, 0.0f));
	this->cageTop->setPosition(Vec2(-4.0f, 58.0f));
}

void BreakableCage::initializeListeners()
{
	super::initializeListeners();

	this->cageBottom->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Entity, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->cage->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Entity, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->cageTop->whenCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Entity, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

Vec2 BreakableCage::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void BreakableCage::onBreak()
{
	this->explosion->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	this->cageBottom->setPhysicsEnabled(true);
	this->cage->setPhysicsEnabled(true);
	this->cageTop->setPhysicsEnabled(true);

	this->cageBottom->setVelocity(Vec2(-12800.0f, 7600.0f));
	this->cage->setVelocity(Vec2(-6400.0f, 5600.0f));
	this->cageTop->setVelocity(Vec2(12800.0f, 9600.0f));
}
