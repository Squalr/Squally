#include "Ram.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

using namespace cocos2d;

const std::string Ram::MapKeyRam = "ram";
const float Ram::AnimOffset = -144.0f - 16.0f;

Ram* Ram::create(ValueMap& properties)
{
	Ram* instance = new Ram(properties);

	instance->autorelease();

	return instance;
}

Ram::Ram(ValueMap& properties) : super(properties)
{
	this->ramAnimations = SmartAnimationNode::create(ObjectResources::Traps_Ram_Animations);
	this->collision = CollisionObject::create(
		CollisionObject::createBox(Size(512.0f, 288.0f)),
		(CollisionType)PlatformerCollisionType::Machine,
		CollisionObject::Properties(true, false)
	);

	this->ramAnimations->setFlippedX(GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyFlipX, Value(false)).asBool());
	this->collision->bindTo(this);
	
	this->addChild(this->ramAnimations);
	this->addChild(this->collision);
}

Ram::~Ram()
{
}

void Ram::onEnter()
{
	super::onEnter();
}

void Ram::initializePositions()
{
	super::initializePositions();

	this->ramAnimations->setPositionY(Ram::AnimOffset);
}

void Ram::initializeListeners()
{
	super::initializeListeners();

	this->collision->whileCollidesWith({ (CollisionType)PlatformerCollisionType::Solid, (CollisionType)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

SmartAnimationNode* Ram::getAnimations()
{
	return this->ramAnimations;
}
