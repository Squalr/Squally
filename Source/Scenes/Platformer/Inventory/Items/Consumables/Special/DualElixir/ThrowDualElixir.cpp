#include "ThrowDualElixir.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Special/DualElixir/DualElixir.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowDualElixir* ThrowDualElixir::create(Priority priority)
{
	ThrowDualElixir* instance = new ThrowDualElixir(priority);

	instance->autorelease();

	return instance;
}

ThrowDualElixir::ThrowDualElixir(Priority priority)
	: super(AttackType::Healing, ItemResources::Consumables_Potions_DualElixir, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowDualElixir::~ThrowDualElixir()
{
}

PlatformerAttack* ThrowDualElixir::cloneInternal()
{
	return ThrowDualElixir::create(this->priority);
}

LocalizedString* ThrowDualElixir::getString()
{
	return Strings::Items_Consumables_Special_DualElixir::create();
}

LocalizedString* ThrowDualElixir::getDescription()
{
	return Strings::Items_Consumables_Special_DualElixirDescription::create()
		->setStringReplacementVariables({
			ConstantString::create(std::to_string(int(DualElixir::RestoreHealthPercentage * 100.0f))),
			ConstantString::create(std::to_string(int(DualElixir::RestoreManaPercentage * 100.0f)))
		});
}

std::string ThrowDualElixir::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowDualElixir::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowDualElixir::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (PlatformerEntity* next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, ItemResources::Consumables_Potions_DualElixir, CSize(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			potion->disable(true);
			
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int healthRestore = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxHealth, 0))) * DualElixir::RestoreHealthPercentage);
				int manaRestore = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxMana, 0))) * DualElixir::RestoreManaPercentage);
				
				CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(owner, entity, healthRestore, this->abilityType));
				CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(owner, entity, manaRestore, this->abilityType));
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

void ThrowDualElixir::onCleanup()
{
}
