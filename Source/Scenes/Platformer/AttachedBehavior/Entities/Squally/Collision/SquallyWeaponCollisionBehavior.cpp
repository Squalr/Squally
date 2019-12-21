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
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyWeaponCollisionBehavior::MapKeyAttachedBehavior = "squally-collisions";

SquallyWeaponCollisionBehavior* SquallyWeaponCollisionBehavior::create(GameObject* owner)
{
	SquallyWeaponCollisionBehavior* instance = new SquallyWeaponCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

SquallyWeaponCollisionBehavior::SquallyWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->squally = dynamic_cast<Squally*>(owner);

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

void SquallyWeaponCollisionBehavior::onWeaponChange()
{
	this->squally->getAttachedBehavior<EntityWeaponCollisionBehavior>([=](EntityWeaponCollisionBehavior* weaponBehavior)
	{
		this->squally->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
		{
			Weapon* weapon = entityInventoryBehavior->getEquipmentInventory()->getWeapon();

			if (weapon != nullptr)
			{
				weaponBehavior->setWeaponSize(weapon->getWeaponCollisionSize());
				weaponBehavior->setWeaponOffset(weapon->getWeaponOffset());
			}
			else
			{
				const Size NoWeaponSize = Size(64.0f, 64.0f);
				const Vec2 NoWeaponOffset = Vec2(0.0f, 96.0f);

				weaponBehavior->setWeaponSize(NoWeaponSize);
				weaponBehavior->setWeaponOffset(NoWeaponOffset);
			}
		});

		weaponBehavior->rebuildWeaponCollision();

		weaponBehavior->weaponCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy }, [=](CollisionObject::CollisionData collisionData)
		{
			if (!this->squally->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				return CollisionObject::CollisionResult::DoNothing;
			}

			PlatformerEnemy* enemy = GameUtils::getFirstParentOfType<PlatformerEnemy>(collisionData.other);

			if (enemy != nullptr && enemy->getStateOrDefaultBool(StateKeys::IsAlive, true))
			{
				// Encountered enemy w/ first-strike
				PlatformerEvents::TriggerEngageEnemy(PlatformerEvents::EngageEnemyArgs(enemy, true));
			}

			return CollisionObject::CollisionResult::DoNothing;
		});
	});
}
