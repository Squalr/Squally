#include "EntityWeaponCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EnginePhysicsTypes.h"
#include "Events/PlatformerEvents.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerPhysicsTypes.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const CSize EntityWeaponCollisionBehavior::DefaultWeaponSize = CSize(64.0f, 128.0f);

EntityWeaponCollisionBehavior::EntityWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->weaponCollisionSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;

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
		this->weaponCollision->setPhysicsFlagEnabled(false);
	}
}

void EntityWeaponCollisionBehavior::enable()
{
	if (this->weaponCollision == nullptr || this->isInvalidated())
	{
		return;
	}

	this->weaponCollision->setPhysicsFlagEnabled(true);
}

void EntityWeaponCollisionBehavior::disable()
{
	if (this->weaponCollision == nullptr || this->isInvalidated())
	{
		return;
	}
	
	this->weaponCollision->setPhysicsFlagEnabled(false);
}

void EntityWeaponCollisionBehavior::setWeaponCollisionSize(CSize weaponCollisionSize)
{
	this->useExplicitWeaponSize = true;
	this->weaponCollisionSize = weaponCollisionSize;
}

void EntityWeaponCollisionBehavior::setWeaponCollisionOffset(Vec2 weaponCollisionOffset)
{
	this->weaponCollisionOffset = weaponCollisionOffset;
}

void EntityWeaponCollisionBehavior::rebuildWeaponCollision(int collisionType)
{
	if (this->isInvalidated() || this->entity == nullptr || this->entity->getAnimations() == nullptr)
	{
		return;
	}
	
	AnimationPart* mainhand = this->entity->getAnimations()->getAnimationPart("mainhand");
	CSize weaponSize = useExplicitWeaponSize ? this->weaponCollisionSize : mainhand->getSpriteSize();

	if (weaponSize.width <= 0.0f || weaponSize.height <= 0.0f)
	{
		weaponSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
	}

	if (mainhand == nullptr)
	{
		return;
	}
	
	if (this->weaponCollision != nullptr)
	{
		mainhand->removeTrackingObject(this->weaponCollision);
	}

	this->weaponCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(weaponSize, 8.0f),
		(CollisionType)collisionType,
		CollisionObject::Properties(false, false)
	);

	Vec2 weaponCollisionOffsetAdjusted = this->entity->getAnimations()->getFlippedX()
		? Vec2(-this->weaponCollisionOffset.x, this->weaponCollisionOffset.y)
		: this->weaponCollisionOffset;

	this->weaponCollision->setPosition(weaponCollisionOffsetAdjusted);
	this->weaponCollision->setPhysicsFlagEnabled(false);
	mainhand->addTrackingObject(this->weaponCollision);
}
