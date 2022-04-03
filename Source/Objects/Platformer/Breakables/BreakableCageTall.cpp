#include "BreakableCageTall.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationSequenceNode.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"

#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/FXResources.h"
#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string BreakableCageTall::MapKey = "breakable-cage-tall";

BreakableCageTall* BreakableCageTall::create(ValueMap& properties)
{
	BreakableCageTall* instance = new BreakableCageTall(properties);

	instance->autorelease();

	return instance;
}

BreakableCageTall::BreakableCageTall(ValueMap& properties, int requiredHits) : super(properties, CSize(196.0f, 112.0f + 64.0f), requiredHits)
{
	this->cageBottom = CollisionObject::create(CollisionObject::createBox(CSize(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->cagedContentNode = Node::create();
	this->cageSideBottom = CollisionObject::create(CollisionObject::createBox(CSize(160.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->cageSideTop = CollisionObject::create(CollisionObject::createBox(CSize(160.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->cageTop = CollisionObject::create(CollisionObject::createBox(CSize(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->explosion = SmartAnimationSequenceNode::create();
	this->breakSound = WorldSound::create(SoundResources::Platformer_Objects_WoodBreak_WoodBreak1);

	this->cageBottom->addChild(Sprite::create(ObjectResources::Breakables_CageBottom));
	this->cageSideBottom->addChild(Sprite::create(ObjectResources::Breakables_CageTallSideBottom));
	this->cageSideTop->addChild(Sprite::create(ObjectResources::Breakables_CageTallSideTop));
	this->cageTop->addChild(Sprite::create(ObjectResources::Breakables_CageTop));

	this->cageBottom->setPhysicsEnabled(false);
	this->cageSideBottom->setPhysicsEnabled(false);
	this->cageSideTop->setPhysicsEnabled(false);
	this->cageTop->setPhysicsEnabled(false);

	this->contentNode->addChild(this->cageBottom);
	this->contentNode->addChild(this->cagedContentNode);
	this->contentNode->addChild(this->cageSideBottom);
	this->contentNode->addChild(this->cageSideTop);
	this->contentNode->addChild(this->cageTop);
	this->contentNode->addChild(this->explosion);
	this->contentNode->addChild(this->breakSound);
}

BreakableCageTall::~BreakableCageTall()
{
}

void BreakableCageTall::initializePositions()
{
	super::initializePositions();

	this->cageBottom->setPosition(Vec2(0.0f, -48.0f));
	this->contentNode->setPosition(Vec2(0.0f, 0.0f));
	this->cageSideBottom->setPosition(Vec2(0.0f, 0.0f));
	this->cageSideTop->setPosition(Vec2(0.0f, 94.0f));
	this->cageTop->setPosition(Vec2(-4.0f, 94.0f + 58.0f));
}

void BreakableCageTall::initializeListeners()
{
	super::initializeListeners();

	this->cageBottom->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->cageSideBottom->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->cageSideTop->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->cageTop->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});
}

Vec2 BreakableCageTall::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void BreakableCageTall::onBreak()
{
	super::onBreak();
	
	this->explosion->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	this->cageBottom->setPhysicsEnabled(true);
	this->cageSideBottom->setPhysicsEnabled(true);
	this->cageSideTop->setPhysicsEnabled(true);
	this->cageTop->setPhysicsEnabled(true);
	this->breakSound->play();

	this->cageBottom->setVelocity(Vec2(-12800.0f, 7600.0f));
	this->cageSideBottom->setVelocity(Vec2(-6400.0f, 5600.0f));
	this->cageSideTop->setVelocity(Vec2(6400.0f, 5600.0f));
	this->cageTop->setVelocity(Vec2(12800.0f, 9600.0f));
}
