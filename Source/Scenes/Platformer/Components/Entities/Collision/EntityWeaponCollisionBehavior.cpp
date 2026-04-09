#include "EntityWeaponCollisionBehavior.h"

#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"

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
	
	if (this->mainhandWeaponCollision != nullptr)
	{
		this->mainhandWeaponCollision->setPhysicsFlagEnabled(false);
	}
	
	if (this->offhandWeaponCollision != nullptr)
	{
		this->offhandWeaponCollision->setPhysicsFlagEnabled(false);
	}
}

void EntityWeaponCollisionBehavior::enable()
{
	if (this->isInvalidated())
	{
		return;
	}

	if (this->mainhandWeaponCollision != nullptr)
	{
		this->mainhandWeaponCollision->setPhysicsFlagEnabled(true);
	}

	if (this->offhandWeaponCollision != nullptr)
	{
		this->offhandWeaponCollision->setPhysicsFlagEnabled(true);
	}
}

void EntityWeaponCollisionBehavior::disable()
{
	if (this->isInvalidated())
	{
		return;
	}
	
	if (this->mainhandWeaponCollision != nullptr)
	{
		this->mainhandWeaponCollision->setPhysicsFlagEnabled(false);
	}
	
	if (this->offhandWeaponCollision != nullptr)
	{
		this->offhandWeaponCollision->setPhysicsFlagEnabled(false);
	}
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

void EntityWeaponCollisionBehavior::rebuildWeaponCollision(int collisionType, bool buildOffhand)
{
	if (this->isInvalidated() || this->entity == nullptr || this->entity->getAnimations() == nullptr)
	{
		return;
	}
	
	AnimationPart* mainhand = this->entity->getAnimations()->getAnimationPart("mainhand");
	AnimationPart* offhand = this->entity->getAnimations()->getAnimationPart("offhand");

	if (mainhand != nullptr)
	{
		CSize weaponSize = useExplicitWeaponSize ? this->weaponCollisionSize : mainhand->getSpriteSize();

		if (weaponSize.width <= 0.0f || weaponSize.height <= 0.0f)
		{
			weaponSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
		}

		if (mainhand == nullptr)
		{
			return;
		}
		
		if (this->mainhandWeaponCollision != nullptr)
		{
			mainhand->removeTrackingObject(this->mainhandWeaponCollision);
		}

		this->mainhandWeaponCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(weaponSize, 8.0f),
			(CollisionType)collisionType,
			CollisionObject::Properties(false, false)
		);

		Vec2 weaponCollisionOffsetAdjusted = this->entity->getAnimations()->getFlippedX()
			? Vec2(-this->weaponCollisionOffset.x, this->weaponCollisionOffset.y)
			: this->weaponCollisionOffset;
		Vec2 trackedObjectOffsetAdjusted = this->entity->getAnimations()->usesNewAnimationSystem()
			? mainhand->getOffset()
			: Vec2::ZERO;

		if (this->entity->getAnimations()->getFlippedX())
		{
			trackedObjectOffsetAdjusted.x *= -1.0f;
		}

		this->mainhandWeaponCollision->setPosition(weaponCollisionOffsetAdjusted + trackedObjectOffsetAdjusted);
		this->mainhandWeaponCollision->setPhysicsFlagEnabled(false);
		mainhand->addTrackingObject(this->mainhandWeaponCollision);
	}

	if (offhand != nullptr && buildOffhand)
	{
		CSize weaponSize = useExplicitWeaponSize ? this->weaponCollisionSize : offhand->getSpriteSize();

		if (weaponSize.width <= 0.0f || weaponSize.height <= 0.0f)
		{
			weaponSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;
		}

		if (offhand == nullptr)
		{
			return;
		}
		
		if (this->offhandWeaponCollision != nullptr)
		{
			offhand->removeTrackingObject(this->offhandWeaponCollision);
		}

		this->offhandWeaponCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(weaponSize, 8.0f),
			(CollisionType)collisionType,
			CollisionObject::Properties(false, false)
		);

		Vec2 weaponCollisionOffsetAdjusted = this->entity->getAnimations()->getFlippedX()
			? Vec2(-this->weaponCollisionOffset.x, this->weaponCollisionOffset.y)
			: this->weaponCollisionOffset;
		Vec2 trackedObjectOffsetAdjusted = this->entity->getAnimations()->usesNewAnimationSystem()
			? offhand->getOffset()
			: Vec2::ZERO;

		if (this->entity->getAnimations()->getFlippedX())
		{
			trackedObjectOffsetAdjusted.x *= -1.0f;
		}

		this->offhandWeaponCollision->setPosition(weaponCollisionOffsetAdjusted + trackedObjectOffsetAdjusted);
		this->offhandWeaponCollision->setPhysicsFlagEnabled(false);
		offhand->addTrackingObject(this->offhandWeaponCollision);
	}
}
