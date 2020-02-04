#include "ThrowRestorePotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestoreHealth.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowRestorePotion* ThrowRestorePotion::create()
{
	ThrowRestorePotion* instance = new ThrowRestorePotion();

	instance->autorelease();

	return instance;
}

ThrowRestorePotion::ThrowRestorePotion() : super(AttackType::Healing, ObjectResources::Items_Consumables_Potions_HEALTH_2, 0.5f, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Combat_Attacks_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowRestorePotion::~ThrowRestorePotion()
{
}

PlatformerAttack* ThrowRestorePotion::cloneInternal()
{
	return ThrowRestorePotion::create();
}

LocalizedString* ThrowRestorePotion::getString()
{
	return Strings::Items_Consumables_Health_RestorePotion::create();
}

std::string ThrowRestorePotion::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowRestorePotion::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowRestorePotion::performAttack(PlatformerEntity* owner, PlatformerEntity* target)
{
	super::performAttack(owner, target);

	ThrownObject* potion = ThrownObject::create(owner, ObjectResources::Items_Consumables_Potions_HEALTH_2, Size(64.0f, 64.0f));
	
	potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionObject::CollisionData collisionData)
	{
		potion->disable(true);

		PlatformerEntity* entity = GameUtils::getFirstParentOfType<PlatformerEntity>(collisionData.other, true);

		if (entity != nullptr)
		{
			entity->getAttachedBehavior<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
			{
				entityBuffBehavior->applyBuff(RestoreHealth::create(owner, entity, RestorePotion::HealTicks));
			});
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

void ThrowRestorePotion::onCleanup()
{
}
