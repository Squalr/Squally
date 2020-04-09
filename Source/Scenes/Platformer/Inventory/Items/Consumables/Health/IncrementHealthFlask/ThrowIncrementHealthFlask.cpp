#include "ThrowIncrementHealthFlask.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealth.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowIncrementHealthFlask* ThrowIncrementHealthFlask::create(Priority priority)
{
	ThrowIncrementHealthFlask* instance = new ThrowIncrementHealthFlask(priority);

	instance->autorelease();

	return instance;
}

ThrowIncrementHealthFlask::ThrowIncrementHealthFlask(Priority priority) : super(AttackType::Healing, ItemResources::Consumables_Potions_HealthFlaskIncrement, priority, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowIncrementHealthFlask::~ThrowIncrementHealthFlask()
{
}

PlatformerAttack* ThrowIncrementHealthFlask::cloneInternal()
{
	return ThrowIncrementHealthFlask::create(this->priority);
}

LocalizedString* ThrowIncrementHealthFlask::getString()
{
	return Strings::Items_Consumables_Health_IncrementHealthFlask::create();
}

std::string ThrowIncrementHealthFlask::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowIncrementHealthFlask::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

bool ThrowIncrementHealthFlask::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	const float WeakPercentage = 0.5f;

	for (auto entity : sameTeam)
	{
		int health = entity->getStateOrDefaultInt(StateKeys::Health, 0);
		int maxHealth = entity->getStateOrDefaultInt(StateKeys::MaxHealth, 0);
		bool isAlive = entity->getStateOrDefaultBool(StateKeys::IsAlive, true);

		if (isAlive && maxHealth >= 0 && std::round(float(health) / float(maxHealth)) <= WeakPercentage)
		{
			return true;
		}
	}

	return false;
}

void ThrowIncrementHealthFlask::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, ItemResources::Consumables_Potions_HealthFlaskIncrement, Size(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
		{
			potion->disable(true);

			PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				entity->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
				{
					entityBuffBehavior->applyBuff(IncrementHealth::create(owner, entity, IncrementHealthFlask::HealTicks));
				});
			}

			return CollisionObject::CollisionResult::DoNothing;
		});

		this->replaceOffhandWithProjectile(owner, potion);

		next->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			if (owner == next)
			{
				potion->launchTowardsTarget(behavior->getTarget(), Vec2(0.0f, 384.0f), 0.25f, Vec3(0.0f, 0.75f, 0.0f));
			}
			else
			{
				potion->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.25f, Vec3(0.75f, 0.75f, 0.75f));
			}
		});
	}
}

void ThrowIncrementHealthFlask::onCleanup()
{
}
