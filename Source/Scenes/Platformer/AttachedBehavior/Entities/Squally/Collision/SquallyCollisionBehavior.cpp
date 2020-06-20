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
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyCollisionBehavior::MapKey = "squally-collisions";
const float SquallyCollisionBehavior::DefaultNoCombatDuration = 2.0f;

SquallyCollisionBehavior* SquallyCollisionBehavior::create(GameObject* owner)
{
	SquallyCollisionBehavior* instance = new SquallyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyCollisionBehavior::SquallyCollisionBehavior(GameObject* owner) : super(owner, (int)PlatformerCollisionType::Player)
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

void SquallyCollisionBehavior::onLoad()
{
	super::onLoad();
	
	this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEngageEnemy, [=](EventCustom* eventCustom)
	{
		this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventLoadRespawn, [=](EventCustom* eventCustom)
	{
		this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;
	}));

	this->squally->watchForAttachedBehavior<EntityGroundCollisionBehavior>([=](EntityGroundCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->setName("Squally entity collision");
		
		if (collisionBehavior->groundCollision == nullptr)
		{
			return;
		}

		collisionBehavior->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidPlayerOnly }, [=](CollisionObject::CollisionData collisionData)
		{
			collisionBehavior->onCollideWithGround();
			
			return CollisionObject::CollisionResult::CollideWithPhysics;
		});
	});

	this->squally->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* collisionBehavior)
	{
		if (collisionBehavior->movementCollision == nullptr)
		{
			return;
		}

		collisionBehavior->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidPlayerOnly }, [=](CollisionObject::CollisionData collisionData)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		});

		collisionBehavior->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::KillPlane, }, [=](CollisionObject::CollisionData collisionData)
		{
			this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
			{
				healthBehavior->kill();
			});

			return CollisionObject::CollisionResult::CollideWithPhysics;
		});
	});

	this->scheduleUpdate();
}

void SquallyCollisionBehavior::update(float dt)
{
	super::update(dt);

	if (this->noCombatDuration > 0.0f)
	{
		this->noCombatDuration -= dt;
	}
}

void SquallyCollisionBehavior::onDisable()
{
	super::onDisable();
}

void SquallyCollisionBehavior::onEntityCollisionCreated()
{
	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->noCombatDuration > 0.0f || !this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		this->noCombatDuration = SquallyCollisionBehavior::DefaultNoCombatDuration;

		PlatformerEnemy* enemy = GameUtils::getFirstParentOfType<PlatformerEnemy>(collisionData.other);

		if (enemy != nullptr && enemy->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
		{
			// Encountered enemy body/weapon -- not a first-strike
			PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, false));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::KillPlane, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->squally->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
		{
			healthBehavior->kill();
		});

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, (int)PlatformerCollisionType::Helper, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}
