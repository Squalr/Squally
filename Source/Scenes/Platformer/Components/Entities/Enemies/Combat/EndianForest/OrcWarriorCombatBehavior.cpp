#include "OrcWarriorCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/ThrowWeapon.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcWarriorCombatBehavior::MapKey = "orc-warrior-combat";

OrcWarriorCombatBehavior* OrcWarriorCombatBehavior::create(GameObject* owner)
{
	OrcWarriorCombatBehavior* instance = new OrcWarriorCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcWarriorCombatBehavior::OrcWarriorCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.15f);
}

OrcWarriorCombatBehavior::~OrcWarriorCombatBehavior()
{
}

void OrcWarriorCombatBehavior::initializePositions()
{
}

void OrcWarriorCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(ThrowWeapon::create(0.55f, EntityAttackBehavior::DefaultRecoverSpeedSlow, PlatformerAttack::Priority::VeryCommon));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Rare));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(IncrementHealthFlask::create());
		}
	});
}
