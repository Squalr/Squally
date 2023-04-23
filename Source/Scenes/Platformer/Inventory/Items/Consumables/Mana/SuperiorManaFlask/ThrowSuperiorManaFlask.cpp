#include "ThrowSuperiorManaFlask.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/SuperiorManaFlask/SuperiorManaFlask.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowSuperiorManaFlask* ThrowSuperiorManaFlask::create(Priority priority)
{
	ThrowSuperiorManaFlask* instance = new ThrowSuperiorManaFlask(priority);

	instance->autorelease();

	return instance;
}

ThrowSuperiorManaFlask::ThrowSuperiorManaFlask(Priority priority)
	: super(AttackType::Healing, ItemResources::Consumables_Potions_ManaFlaskSuperior, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowSuperiorManaFlask::~ThrowSuperiorManaFlask()
{
}

PlatformerAttack* ThrowSuperiorManaFlask::cloneInternal()
{
	return ThrowSuperiorManaFlask::create(this->priority);
}

LocalizedString* ThrowSuperiorManaFlask::getString()
{
	return Strings::Items_Consumables_Mana_SuperiorManaFlask::create();
}

LocalizedString* ThrowSuperiorManaFlask::getDescription()
{
	return Strings::Items_Consumables_Mana_SuperiorManaFlaskDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(SuperiorManaFlask::RestorePercentage * 100.0f))));
}

std::string ThrowSuperiorManaFlask::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowSuperiorManaFlask::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowSuperiorManaFlask::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (PlatformerEntity* next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, ItemResources::Consumables_Potions_ManaFlaskSuperior, CSize(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			potion->disable(true);
			
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int restore = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxMana, 0))) * SuperiorManaFlask::RestorePercentage);
				
				CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(owner, entity, restore, this->abilityType));
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

void ThrowSuperiorManaFlask::onCleanup()
{
}
