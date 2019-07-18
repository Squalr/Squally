#include "BreakableBase.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsBody.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

using namespace cocos2d;

BreakableBase::BreakableBase(ValueMap& initProperties, Size collisionSize, int requiredHits) : super(initProperties)
{
	this->breakableCollision = CollisionObject::create(PhysicsBody::createBox(collisionSize), (CollisionType)(PlatformerCollisionType::Breakable), false, false);
	
	this->hasBroke = false;

	this->addChild(this->breakableCollision);
}

BreakableBase::~BreakableBase()
{
}

void BreakableBase::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void BreakableBase::initializePositions()
{
	super::initializePositions();
}

void BreakableBase::initializeListeners()
{
	super::initializeListeners();

	this->breakableCollision->whenCollidesWith({(int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData data)
	{
		if (!this->hasBroke)
		{
			this->hasBroke = true;
			this->onBreak();
		}

		this->breakableCollision->setPhysicsEnabled(false);

		return CollisionObject::CollisionResult::DoNothing;
	});
}
