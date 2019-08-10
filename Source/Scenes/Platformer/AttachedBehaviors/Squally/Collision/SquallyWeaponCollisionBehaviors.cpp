#include "SquallyWeaponCollisionBehaviors.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityWeaponCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Stats/EntityHealthBehaviorBase.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string SquallyWeaponCollisionBehaviors::MapKeyAttachedBehavior = "squally-collisions";

SquallyWeaponCollisionBehaviors* SquallyWeaponCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyWeaponCollisionBehaviors* instance = new SquallyWeaponCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyWeaponCollisionBehaviors::SquallyWeaponCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->squally = static_cast<Squally*>(owner);

	if (this->squally == nullptr)
	{
		this->invalidate();
	}
}

SquallyWeaponCollisionBehaviors::~SquallyWeaponCollisionBehaviors()
{
}

void SquallyWeaponCollisionBehaviors::onLoad()
{
	this->onWeaponChange();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEquippedItemsChanged, [=](EventCustom*)
	{
		this->onWeaponChange();
	}));

	EntityWeaponCollisionBehaviors* weaponBehaviors = this->squally->getAttachedBehavior<EntityWeaponCollisionBehaviors>();
	EntityHealthBehaviorBase* health = this->squally->getAttachedBehavior<EntityHealthBehaviorBase>();

	if (weaponBehaviors != nullptr)
	{
		weaponBehaviors->weaponCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionObject::CollisionData collisionData)
		{
			if (health->isDead())
			{
				return CollisionObject::CollisionResult::DoNothing;
			}

			PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());
			
			// First-strike!
			// this->engageEnemy(enemy, true);

			return CollisionObject::CollisionResult::DoNothing;
		});
	}
}

void SquallyWeaponCollisionBehaviors::onWeaponChange()
{
	EntityWeaponCollisionBehaviors* weaponBehaviors = this->squally->getAttachedBehavior<EntityWeaponCollisionBehaviors>();
	Weapon* weapon = this->squally->getEquipmentInventory()->getWeapon();

	if (weapon != nullptr)
	{
		weaponBehaviors->setWeaponSize(weapon->getWeaponCollisionSize());
		weaponBehaviors->setWeaponOffset(weapon->getWeaponOffset());
	}
	else
	{
		const Size NoWeaponSize = Size(64.0f, 64.0f);
		const Vec2 NoWeaponOffset = Vec2(0.0f, 96.0f);

		weaponBehaviors->setWeaponSize(NoWeaponSize);
		weaponBehaviors->setWeaponOffset(NoWeaponOffset);
	}

	weaponBehaviors->rebuildWeaponCollision();
}
