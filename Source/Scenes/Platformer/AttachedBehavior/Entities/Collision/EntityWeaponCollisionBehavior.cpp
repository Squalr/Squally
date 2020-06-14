#include "EntityWeaponCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const Size EntityWeaponCollisionBehavior::DefaultWeaponSize = Size(64.0f, 128.0f);

EntityWeaponCollisionBehavior::EntityWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->weaponCollisionSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
	this->weaponCollisionOffset = Vec2::ZERO;
	this->weaponCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityWeaponCollisionBehavior::~EntityWeaponCollisionBehavior()
{
}

void EntityWeaponCollisionBehavior::onLoad()
{
}

void EntityWeaponCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->weaponCollision != nullptr)
	{
		this->weaponCollision->setPhysicsEnabled(false);
	}
}

void EntityWeaponCollisionBehavior::enable()
{
	if (this->weaponCollision == nullptr || this->isInvalidated())
	{
		return;
	}

	this->weaponCollision->setPhysicsEnabled(true);
}

void EntityWeaponCollisionBehavior::disable()
{
	if (this->weaponCollision == nullptr || this->isInvalidated())
	{
		return;
	}
	
	this->weaponCollision->setPhysicsEnabled(false);
}

void EntityWeaponCollisionBehavior::setWeaponCollisionSize(Size weaponCollisionSize)
{
	this->weaponCollisionSize = weaponCollisionSize;
}

void EntityWeaponCollisionBehavior::setWeaponCollisionOffset(Vec2 weaponCollisionOffset)
{
	this->weaponCollisionOffset = weaponCollisionOffset;
}

void EntityWeaponCollisionBehavior::rebuildWeaponCollision(int collisionType)
{
	if (this->isInvalidated())
	{
		return;
	}
	
	AnimationPart* mainhand = this->entity->getAnimations()->getAnimationPart("mainhand");

	if (mainhand == nullptr)
	{
		return;
	}
	
	if (this->weaponCollision != nullptr)
	{
		mainhand->removeTrackingObject(this->weaponCollision);
	}

	this->weaponCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->weaponCollisionSize, 8.0f),
		(CollisionType)collisionType,
		CollisionObject::Properties(false, false)
	);

	this->weaponCollision->setPosition(this->weaponCollisionOffset);
	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}
