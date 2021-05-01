#include "EnemyWeaponCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityWeaponCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EnemyWeaponCollisionBehavior::MapKey = "enemy-weapon-collision";

EnemyWeaponCollisionBehavior* EnemyWeaponCollisionBehavior::create(GameObject* owner)
{
	EnemyWeaponCollisionBehavior* instance = new EnemyWeaponCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EnemyWeaponCollisionBehavior::EnemyWeaponCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EnemyWeaponCollisionBehavior::~EnemyWeaponCollisionBehavior()
{
}

void EnemyWeaponCollisionBehavior::onLoad()
{
	this->defer([=]()
	{
		this->rebuildWeaponCollision((int)PlatformerCollisionType::EnemyWeapon);
	});
}

void EnemyWeaponCollisionBehavior::onDisable()
{
	super::onDisable();
}
