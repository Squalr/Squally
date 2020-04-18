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
	this->weaponSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
	this->weaponOffset = Vec2::ZERO;
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

void EntityWeaponCollisionBehavior::setWeaponSize(Size weaponSize)
{
	this->weaponSize = weaponSize;
}

void EntityWeaponCollisionBehavior::setWeaponOffset(Vec2 weaponOffset)
{
	this->weaponOffset = weaponOffset;
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
		CollisionObject::createCapsulePolygon(this->weaponSize, 8.0f),
		(CollisionType)collisionType,
		CollisionObject::Properties(false, false)
	);

	this->weaponCollision->setPosition(this->weaponOffset);
	this->weaponCollision->setPhysicsEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}
