#include "ThrowHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion/HealthPotion.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowHealthPotion* ThrowHealthPotion::create(Priority priority, float healPercentage, std::string iconResource)
{
	ThrowHealthPotion* instance = new ThrowHealthPotion(priority, healPercentage, iconResource);

	instance->autorelease();

	return instance;
}

ThrowHealthPotion::ThrowHealthPotion(Priority priority, float healPercentage, std::string iconResource)
	: super(AttackType::Healing, iconResource, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);
	this->healPercentage = healPercentage;

	this->addChild(this->throwSound);
	this->addChild(this->healSound);
}

ThrowHealthPotion::~ThrowHealthPotion()
{
}

PlatformerAttack* ThrowHealthPotion::cloneInternal()
{
	return ThrowHealthPotion::create(this->priority, this->healPercentage, this->getIconResource());
}

LocalizedString* ThrowHealthPotion::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

std::string ThrowHealthPotion::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowHealthPotion::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowHealthPotion::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (auto next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, this->getIconResource(), Size(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
		{
			potion->disable(true);
			
			PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int healing = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxHealth, 0))) * this->healPercentage);

				this->healSound->play();
				CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(owner, entity, healing, this->abilityType));
			}

			return CollisionObject::CollisionResult::DoNothing;
		});

		this->replaceOffhandWithProjectile(owner, potion);

		next->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			if (owner == next)
			{
				potion->launchTowardsTarget3D(behavior->getTarget(), Vec2(0.0f, 384.0f), 0.25f, Vec3(0.0f, 0.75f, 0.0f));
			}
			else
			{
				potion->launchTowardsTarget3D(behavior->getTarget(), Vec2::ZERO, 0.25f, Vec3(0.75f, 0.75f, 0.75f));
			}
		});
	}
}

void ThrowHealthPotion::onCleanup()
{
}
