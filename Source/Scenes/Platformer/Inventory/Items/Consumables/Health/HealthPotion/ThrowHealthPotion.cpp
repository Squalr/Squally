#include "ThrowHealthPotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Projectiles/Combat/ThrownObject/ThrownObject.h"
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

ThrowHealthPotion::ThrowHealthPotion(Priority priority, float healPercentage, std::string iconResource) : super(AttackType::Healing, iconResource, priority, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Projectiles_ItemThrow1);
	this->healPercentage = healPercentage;

	this->addChild(this->throwSound);
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
	return Strings::Common_Empty::create();
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

void ThrowHealthPotion::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);
	
	ThrownObject* potion = ThrownObject::create(owner, target, false, this->getIconResource(), Size(64.0f, 64.0f));
	
	potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		potion->disable(true);
		
		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			int healing = int(std::round(float(entity->getStateOrDefaultInt(StateKeys::MaxHealth, 0))) * this->healPercentage);

			CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(owner, entity, healing));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->replaceOffhandWithProjectile(owner, potion);

	target->getAttachedBehavior<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
	{
		if (owner == target)
		{
			potion->launchTowardsTarget(behavior->getTarget(), Vec2(0.0f, 384.0f), 0.25f, Vec3(0.0f, 0.75f, 0.0f));
		}
		else
		{
			potion->launchTowardsTarget(behavior->getTarget(), Vec2::ZERO, 0.25f, Vec3(0.75f, 0.75f, 0.75f));
		}
	});
}

void ThrowHealthPotion::onCleanup()
{
}
