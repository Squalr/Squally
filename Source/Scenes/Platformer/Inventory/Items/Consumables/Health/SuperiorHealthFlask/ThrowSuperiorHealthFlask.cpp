#include "ThrowSuperiorHealthFlask.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/SuperiorHealthFlask.h"
#include "Scenes/Platformer/Level/Combat/Physics/CombatCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ItemResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

ThrowSuperiorHealthFlask* ThrowSuperiorHealthFlask::create(Priority priority)
{
	ThrowSuperiorHealthFlask* instance = new ThrowSuperiorHealthFlask(priority);

	instance->autorelease();

	return instance;
}

ThrowSuperiorHealthFlask::ThrowSuperiorHealthFlask(Priority priority)
	: super(AttackType::Healing, ItemResources::Consumables_Potions_HealthPotionGreater, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);
	this->healSound = WorldSound::create(SoundResources::Platformer_Spells_Heal2);

	this->addChild(this->throwSound);
	this->addChild(this->healSound);
}

ThrowSuperiorHealthFlask::~ThrowSuperiorHealthFlask()
{
}

PlatformerAttack* ThrowSuperiorHealthFlask::cloneInternal()
{
	return ThrowSuperiorHealthFlask::create(this->priority);
}

LocalizedString* ThrowSuperiorHealthFlask::getString()
{
	return Strings::Items_Consumables_Health_HealthPotion::create();
}

LocalizedString* ThrowSuperiorHealthFlask::getDescription()
{
	return Strings::Items_Consumables_Health_HealthPotionDescription::create()
		->setStringReplacementVariables(ConstantString::create(std::to_string(int(SuperiorHealthFlask::HealPercentage * 100.0f))));
}

std::string ThrowSuperiorHealthFlask::getAttackAnimation()
{
	return "ThrowItem";
}

void ThrowSuperiorHealthFlask::onAttackTelegraphBegin()
{
	super::onAttackTelegraphBegin();
	
	this->throwSound->play(false, this->attackDuration / 2.0f);
}

void ThrowSuperiorHealthFlask::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
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
				int healing = int(std::round(float(entity->getRuntimeStateOrDefaultInt(StateKeys::MaxHealth, 0))) * SuperiorHealthFlask::HealPercentage);

				this->healSound->play();
				CombatEvents::TriggerHealing(CombatEvents::DamageOrHealingArgs(owner, entity, healing, this->abilityType));
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

void ThrowSuperiorHealthFlask::onCleanup()
{
}
