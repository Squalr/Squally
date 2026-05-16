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
	this->offhandWeaponCollisionSize = EntityWeaponCollisionBehavior::DefaultWeaponSize;

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

CollisionObject* EntityWeaponCollisionBehavior::getMainhandWeaponCollision() const
{
	return this->mainhandWeaponCollision;
}

CollisionObject* EntityWeaponCollisionBehavior::getOffhandWeaponCollision() const
{
	return this->offhandWeaponCollision;
}

Vec2 EntityWeaponCollisionBehavior::getWeaponCollisionOffset() const
{
	return this->weaponCollisionOffset;
}

Vec2 EntityWeaponCollisionBehavior::getOffhandWeaponCollisionOffset() const
{
	return this->offhandWeaponCollisionOffset;
}

Vec2 EntityWeaponCollisionBehavior::getWeaponCollisionDebugOffset() const
{
	return this->weaponCollisionDebugOffset;
}

Vec2 EntityWeaponCollisionBehavior::getOffhandWeaponCollisionDebugOffset() const
{
	return this->offhandWeaponCollisionDebugOffset;
}

void EntityWeaponCollisionBehavior::setWeaponCollisionDebugOffset(Vec2 weaponCollisionDebugOffset)
{
	this->weaponCollisionDebugOffset = weaponCollisionDebugOffset;
	this->refreshWeaponCollisionOffsets();
}

void EntityWeaponCollisionBehavior::setOffhandWeaponCollisionDebugOffset(Vec2 weaponCollisionDebugOffset)
{
	this->offhandWeaponCollisionDebugOffset = weaponCollisionDebugOffset;
	this->refreshWeaponCollisionOffsets();
}

void EntityWeaponCollisionBehavior::setWeaponCollisionSize(CSize weaponCollisionSize)
{
	this->useExplicitWeaponSize = true;
	this->weaponCollisionSize = weaponCollisionSize;
}

void EntityWeaponCollisionBehavior::setWeaponCollisionOffset(Vec2 weaponCollisionOffset)
{
	this->weaponCollisionOffset = weaponCollisionOffset;
	this->refreshWeaponCollisionOffsets();
}

void EntityWeaponCollisionBehavior::setOffhandWeaponCollisionSize(CSize weaponCollisionSize)
{
	this->useExplicitOffhandWeaponSize = true;
	this->offhandWeaponCollisionSize = weaponCollisionSize;
}

void EntityWeaponCollisionBehavior::setOffhandWeaponCollisionOffset(Vec2 weaponCollisionOffset)
{
	this->offhandWeaponCollisionOffset = weaponCollisionOffset;
	this->refreshWeaponCollisionOffsets();
}

void EntityWeaponCollisionBehavior::refreshWeaponCollisionOffsets()
{
	if (this->isInvalidated() || this->entity == nullptr || this->entity->getAnimations() == nullptr)
	{
		return;
	}

	const Vec2 resolvedWeaponCollisionOffset = this->weaponCollisionOffset + this->weaponCollisionDebugOffset;
	const Vec2 resolvedOffhandWeaponCollisionOffset = this->offhandWeaponCollisionOffset + this->offhandWeaponCollisionDebugOffset;
	const Vec2 weaponCollisionOffsetAdjusted = this->entity->getAnimations()->getFlippedX()
		? Vec2(-resolvedWeaponCollisionOffset.x, resolvedWeaponCollisionOffset.y)
		: resolvedWeaponCollisionOffset;
	const Vec2 offhandWeaponCollisionOffsetAdjusted = this->entity->getAnimations()->getFlippedX()
		? Vec2(-resolvedOffhandWeaponCollisionOffset.x, resolvedOffhandWeaponCollisionOffset.y)
		: resolvedOffhandWeaponCollisionOffset;

	if (this->mainhandWeaponCollision != nullptr)
	{
		this->mainhandWeaponCollision->setPosition(weaponCollisionOffsetAdjusted);
	}

	if (this->offhandWeaponCollision != nullptr)
	{
		this->offhandWeaponCollision->setPosition(offhandWeaponCollisionOffsetAdjusted);
	}
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
		CSize weaponSize = this->useExplicitWeaponSize ? this->weaponCollisionSize : mainhand->getSpriteSize();

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

		this->mainhandWeaponCollision->setPhysicsFlagEnabled(false);
		mainhand->addTrackingObject(this->mainhandWeaponCollision);
	}

	if (!buildOffhand || offhand == nullptr)
	{
		if (this->offhandWeaponCollision != nullptr)
		{
			if (offhand != nullptr)
			{
				offhand->removeTrackingObject(this->offhandWeaponCollision);
			}
			else if (this->offhandWeaponCollision->getParent() != nullptr)
			{
				this->offhandWeaponCollision->removeFromParent();
			}

			this->offhandWeaponCollision = nullptr;
		}
	}
	else
	{
		CSize weaponSize = this->useExplicitOffhandWeaponSize ? this->offhandWeaponCollisionSize : offhand->getSpriteSize();

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

		this->offhandWeaponCollision->setPhysicsFlagEnabled(false);
		offhand->addTrackingObject(this->offhandWeaponCollision);
	}

	this->refreshWeaponCollisionOffsets();
}
