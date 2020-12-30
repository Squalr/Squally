#include "BreakableCage.h"

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

const std::string BreakableCage::MapKey = "breakable-cage";

BreakableCage* BreakableCage::create(ValueMap& properties)
{
	BreakableCage* instance = new BreakableCage(properties);

	instance->autorelease();

	return instance;
}

BreakableCage::BreakableCage(ValueMap& properties, int requiredHits) : super(properties, Size(196.0f, 112.0f + 64.0f), requiredHits)
{
	this->cageBottom = CollisionObject::create(CollisionObject::createBox(Size(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->cagedContentNode = Node::create();
	this->cage = CollisionObject::create(CollisionObject::createBox(Size(160.0f, 112.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->cageTop = CollisionObject::create(CollisionObject::createBox(Size(160.0f, 32.0f)), (CollisionType)PlatformerCollisionType::Physics, CollisionObject::Properties(true, true, 0.1f, 0.2f));
	this->explosion = SmartAnimationSequenceNode::create();
	this->breakSound = WorldSound::create(SoundResources::Platformer_Objects_WoodBreak_WoodBreak1);

	this->cageBottom->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageBottom));
	this->cage->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageSide));
	this->cageTop->addChild(Sprite::create(ObjectResources::Collectables_Animals_CageTop));

	this->cageBottom->setPhysicsEnabled(false);
	this->cage->setPhysicsEnabled(false);
	this->cageTop->setPhysicsEnabled(false);

	this->contentNode->addChild(this->cageBottom);
	this->contentNode->addChild(this->cagedContentNode);
	this->contentNode->addChild(this->cage);
	this->contentNode->addChild(this->cageTop);
	this->contentNode->addChild(this->explosion);
	this->contentNode->addChild(this->breakSound);
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

	this->cageBottom->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->cage->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->cageTop->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough, (CollisionType)PlatformerCollisionType::Physics, (CollisionType)PlatformerCollisionType::Player, (CollisionType)PlatformerCollisionType::PlayerWeapon }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});
}

Vec2 BreakableCage::getButtonOffset()
{
	return Vec2(0.0f, 96.0f);
}

void BreakableCage::onBreak()
{
	super::onBreak();
	
	this->explosion->playAnimation(FXResources::ExplosionNormal_Explosion_0000, 0.035f, true);
	this->cageBottom->setPhysicsEnabled(true);
	this->cage->setPhysicsEnabled(true);
	this->cageTop->setPhysicsEnabled(true);
	this->breakSound->play();

	this->cageBottom->setVelocity(Vec2(-12800.0f, 7600.0f));
	this->cage->setVelocity(Vec2(-6400.0f, 5600.0f));
	this->cageTop->setVelocity(Vec2(12800.0f, 9600.0f));
}
