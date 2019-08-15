#include "SquallyCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehavior.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyCollisionBehavior::MapKeyAttachedBehavior = "squally-collisions";
const float SquallyCollisionBehavior::DefaultNoCombatDuration = 2.0f;

SquallyCollisionBehavior* SquallyCollisionBehavior::create(GameObject* owner)
{
	SquallyCollisionBehavior* instance = new SquallyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyCollisionBehavior::SquallyCollisionBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->noCombatDuration = 0.0f;

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyCollisionBehavior::~SquallyCollisionBehavior()
{
}

void SquallyCollisionBehavior::update(float dt)
{
	super::update(dt);

	if (this->noCombatDuration > 0.0f)
	{
		this->noCombatDuration -= dt;
	}
}

void SquallyCollisionBehavior::onLoad()
{
	this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;

	EntityCollisionBehavior* collisionBehavior = this->squally->getAttachedBehavior<EntityCollisionBehavior>();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEngageEnemy, [=](EventCustom* eventCustom)
	{
		this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;
	}));

	if (collisionBehavior != nullptr)
	{
		collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyWeapon }, [=](CollisionObject::CollisionData collisionData)
		{
			if (this->noCombatDuration > 0.0f || !this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				return CollisionObject::CollisionResult::DoNothing;
			}

			this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;

			PlatformerEnemy* enemy = GameUtils::getFirstParentOfType<PlatformerEnemy>(collisionData.other);

			// Encountered enemy body/weapon -- not a first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, false));

			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
		{
			if (this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				this->squally->setState(StateKeys::IsAlive, Value(false));
			}

			return CollisionObject::CollisionResult::DoNothing;
		});
		
		collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
		{
			if (this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");
				
				mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);
			}

			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
		{
			if (this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");

				mouth->replaceSprite(EntityResources::Squally_MOUTH);
			}

			return CollisionObject::CollisionResult::DoNothing;
		});

		collisionBehavior->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionObject::CollisionData collisionData)
		{
			return CollisionObject::CollisionResult::DoNothing;
		});
	}

	this->scheduleUpdate();
}
