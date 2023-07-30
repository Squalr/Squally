#include "ThrowSuperiorHealthFlask.h"

#include "cocos/2d/CCActionInterval.h"

#include "Engine/Localization/ConstantString.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Sound/WorldSound.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Objects/Platformer/Combat/Projectiles/ThrownObject/ThrownObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityProjectileTargetBehavior.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/AddHealth.h"
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
	: super(AttackType::Healing, ItemResources::Consumables_Potions_HealthFlaskSuperior, priority, AbilityType::Arcane, 10, 15, 0, 0.2f, 1.5f)
{
	this->throwSound = WorldSound::create(SoundResources::Platformer_Physical_Projectiles_ItemThrow1);

	this->addChild(this->throwSound);
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
	return Strings::Items_Consumables_Health_SuperiorHealthFlask::create();
}

LocalizedString* ThrowSuperiorHealthFlask::getDescription()
{
	return Strings::Items_Consumables_Health_SuperiorHealthFlaskDescription::create()
		->setStringReplacementVariables({ ConstantString::create(std::to_string(int(SuperiorHealthFlask::HealTicks))), ConstantString::create(std::to_string(int(SuperiorHealthFlask::HealTicks))) });
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

bool ThrowSuperiorHealthFlask::isWorthUsing(PlatformerEntity* caster, const std::vector<PlatformerEntity*>& sameTeam, const std::vector<PlatformerEntity*>& otherTeam)
{
	const float WeakPercentage = 0.5f;

	for (auto entity : sameTeam)
	{
		int health = entity->getRuntimeStateOrDefaultInt(StateKeys::Health, 0);
		int maxHealth = entity->getRuntimeStateOrDefaultInt(StateKeys::MaxHealth, 0);
		bool isAlive = entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true);

		if (isAlive && maxHealth >= 0 && std::round(float(health) / float(maxHealth)) <= WeakPercentage)
		{
			return true;
		}
	}

	return false;
}

void ThrowSuperiorHealthFlask::performAttack(PlatformerEntity* owner, std::vector<PlatformerEntity*> targets)
{
	super::performAttack(owner, targets);

	for (PlatformerEntity* next : targets)
	{
		ThrownObject* potion = ThrownObject::create(owner, next, false, ItemResources::Consumables_Potions_HealthFlaskSuperior, CSize(64.0f, 64.0f));
		
		potion->whenCollidesWith({ (int)CombatCollisionType::EntityEnemy, (int)CombatCollisionType::EntityFriendly }, [=](CollisionData collisionData)
		{
			potion->disable(true);

			PlatformerEntity* entity = GameUtils::GetFirstParentOfType<PlatformerEntity>(collisionData.other, true);

			if (entity != nullptr)
			{
				entity->getComponent<EntityBuffBehavior>([=](EntityBuffBehavior* entityBuffBehavior)
				{
					entityBuffBehavior->applyBuff(AddHealth::create(owner, entity));
				});
			}

			return CollisionResult::DoNothing;
		});

		this->replaceOffhandWithProjectile(owner, potion);

		next->getComponent<EntityProjectileTargetBehavior>([=](EntityProjectileTargetBehavior* behavior)
		{
			if (owner == next)
			{
				// Self launch (aim above self)
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
