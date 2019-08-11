#include "SquallyCollisionBehavior.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyCollisionBehavior::MapKeyAttachedBehavior = "squally-collisions";

SquallyCollisionBehavior* SquallyCollisionBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyCollisionBehavior* instance = new SquallyCollisionBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyCollisionBehavior::SquallyCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);
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
	this->noCombatDuration = 2.0f;

	EntityHealthBehavior* health = this->squally->getAttachedBehavior<EntityHealthBehavior>();

	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying, (int)PlatformerCollisionType::EnemyWeapon }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->noCombatDuration > 0.0f || health->isDead())
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());
		
		// Hit enemy directly, or got hit by their weapon -- not a first-strike
		this->engageEnemy(enemy, false);

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (health->isAlive())
		{
			health->killAndRespawn();
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->squally->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (health->isAlive())
		{
			AnimationPart* mouth = this->squally->getAnimations()->getAnimationPart("mouth");
			
			mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->squally->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		if (health->isAlive())
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

	this->scheduleUpdate();
}

void SquallyCollisionBehavior::engageEnemy(PlatformerEnemy* enemy, bool firstStrike)
{
	this->noCombatDuration = 2.0f;
	this->squally->saveState();

	EntityHealthBehavior* health = enemy->getAttachedBehavior<EntityHealthBehavior>();

	if (enemy != nullptr && health != nullptr && !health->isDead() && enemy->getBattleMapResource() != "")
	{
		CombatMap* combatMap = CombatMap::create(
			enemy->getBattleMapResource(),
			enemy->getBattleMapArgs(),
			firstStrike,
			enemy->getUniqueIdentifier(),
			{ Squally::MapKeySqually, SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value(FlyBot::MapKeyFlyBot)).asString() },
			enemy->getCombatEntityList()
		);

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(combatMap));
	}
}
