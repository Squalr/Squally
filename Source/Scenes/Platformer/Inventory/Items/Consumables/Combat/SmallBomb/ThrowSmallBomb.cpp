#include "ThrowSmallBomb.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Combat/SmallBomb/SmallBomb.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowSmallBomb* ThrowSmallBomb::create(Priority priority)
{
	ThrowSmallBomb* instance = new ThrowSmallBomb(priority);

	instance->autorelease();

	return instance;
}

ThrowSmallBomb::ThrowSmallBomb(Priority priority)
	: super(AttackType::Damage, ItemResources::Consumables_Combat_SmallBomb, priority, AbilityType::Physical, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);
	this->explosionSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);

	this->addChild(this->throwSound);
	this->addChild(this->explosionSound);
}

ThrowSmallBomb::~ThrowSmallBomb()
{
}

PlatformerAttack* ThrowSmallBomb::cloneInternal()
{
	return ThrowSmallBomb::create(this->priority);
}

LocalizedString* ThrowSmallBomb::getString()
{
	return Strings::Items_Consumables_Combat_SmallBomb::create();
}

LocalizedString* ThrowSmallBomb::getDescription()
{
	return Strings::Items_Consumables_Combat_SmallBombDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(SmallBomb::DamageMin)),
			ConstantString::create(std::to_string(SmallBomb::DamageMax))
		});
}

std::string ThrowSmallBomb::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowSmallBomb::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowSmallBomb::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (PlatformerEntity* next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, this->getIconResource(), CSize(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			potion->disable(true);
			
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int damage = RandomHelper::random_int(SmallBomb::DamageMin, SmallBomb::DamageMax);
				this->explosionSound->play();
				CombatEvents::TriggerDamage(CombatEvents::DamageOrHealingArgs(owner, entity, damage, this->abilityType));
			}

			return CollisionResult::DoNothing;
		});

		this->replaceOffhandWithProjectile(owner, potion);

		next->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
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

void ThrowSmallBomb::onCleanup()
{
}
