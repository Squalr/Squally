#include "SquallyWeaponCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyWeaponCollisionBehavior::MapKey = "squally-weapon-collision";

SquallyWeaponCollisionBehavior* SquallyWeaponCollisionBehavior::create(GameObject* owner)
{
	SquallyWeaponCollisionBehavior* instance = new SquallyWeaponCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyWeaponCollisionBehavior::SquallyWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);
	this->canEngage = true;

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyWeaponCollisionBehavior::~SquallyWeaponCollisionBehavior()
{
}

void SquallyWeaponCollisionBehavior::onLoad()
{
	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->rebuildWeaponCollision((int)PlatformerCollisionType::PlayerWeapon);
	}));

	this->defer([=]()
	{
		this->squally->watchForAttachedBehavior<EntityWeaponCollisionBehavior>([=](EntityWeaponCollisionBehavior* weaponBehavior)
		{
			this->onWeaponChange();

			this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
			{
				this->onWeaponChange();
			}));
		});
	});
}

void SquallyWeaponCollisionBehavior::onDisable()
{
	super::onDisable();
}

void SquallyWeaponCollisionBehavior::onWeaponChange()
{
	this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Weapon* weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();

		if (weapon != nullptr)
		{
			this->setWeaponCollisionSize(weapon->getWeaponCollisionSize());
			this->setWeaponCollisionOffset(weapon->getWeaponCollisionOffset());
		}
		else
		{
			const Size NoWeaponSize = Size(64.0f, 64.0f);
			const Vec2 NoWeaponOffset = Vec2(0.0f, 96.0f);

			this->setWeaponCollisionSize(NoWeaponSize);
			this->setWeaponCollisionOffset(NoWeaponOffset);
		}
	});

	this->rebuildWeaponCollision((int)PlatformerCollisionType::PlayerWeapon);

	if (this->weaponCollision != nullptr)
	{
		this->weaponCollision->setName("Squally weapon collision");
		
		this->weaponCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionData collisionData)
		{
			if (!this->canEngage || !this->squally->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				return CollisionResult::DoNothing;
			}

			PlatformerEnemy* enemy = GameUtils::GetFirstParentOfType<PlatformerEnemy>(collisionData.other);

			if (enemy != nullptr && enemy->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				// Encountered enemy w/ first-strike
				PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, true));

				this->canEngage = false;
			}

			return CollisionResult::DoNothing;
		});
	}
}
