#include "SquallyCollisionBehaviors.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/AttachedBehavior/AttachedBehavior.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyCollisionBehaviors::MapKeyAttachedBehavior = "squally-collisions";

SquallyCollisionBehaviors* SquallyCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyCollisionBehaviors* instance = new SquallyCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyCollisionBehaviors::SquallyCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);
}

SquallyCollisionBehaviors::~SquallyCollisionBehaviors()
{
}

void SquallyCollisionBehaviors::onLoad()
{
	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying, (int)PlatformerCollisionType::EnemyWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->squally->noCombatDuration > 0.0f || this->squally->isDead())
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());
		
		// Hit enemy directly, or got hit by their weapon -- not a first-strike
		this->squally->engageEnemy(enemy, false);

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->squally->isAlive())
		{
			this->squally->killAndRespawn();
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->squally->isAlive())
		{
			AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");
			
			mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->squally->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->squally->isAlive())
		{
			AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");

			mouth->replaceSprite(EntityResources::Squally_MOUTH);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
