#include "ThrowManaPotion.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion/ManaPotion.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowManaPotion* ThrowManaPotion::create(Priority priority)
{
	ThrowManaPotion* instance = new ThrowManaPotion(priority);

	instance->autorelease();

	return instance;
}

ThrowManaPotion::ThrowManaPotion(Priority priority)
	: super(AttackType::Healing, ItemResources::Consumables_Potions_ManaPotion, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
}

ThrowManaPotion::~ThrowManaPotion()
{
}

PlatformerAttack* ThrowManaPotion::cloneInternal()
{
	return ThrowManaPotion::create(this->priority);
}

LocalizedString* ThrowManaPotion::getString()
{
	return Strings::Items_Consumables_Mana_ManaPotion::create();
}

LocalizedString* ThrowManaPotion::getDescription()
{
	return Strings::Items_Consumables_Mana_ManaPotionDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(ManaPotion::RestorePercentage * 100.0f))));
}

std::string ThrowManaPotion::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowManaPotion::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowManaPotion::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);
	
	for (auto next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, ItemResources::Consumables_Potions_ManaPotion, Size(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			potion->disable(true);
			
			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				int restore = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxMana, 0))) * ManaPotion::RestorePercentage);
				
				CombatEvents::TriggerManaRestore(CombatEvents::ManaRestoreOrDrainArgs(owner, entity, restore, this->abilityType));
			}

			return CollisionResult::DoNothing;
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

void ThrowManaPotion::onCleanup()
{
}
