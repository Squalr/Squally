#include "OrcBomberCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/OrcBomber/DropTimeBomb.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/ThrowFlamingWeapon.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcBomberCombatBehavior::MapKey = "orc-bomber-combat";

OrcBomberCombatBehavior* OrcBomberCombatBehavior::create(GameObject* owner)
{
	OrcBomberCombatBehavior* instance = new OrcBomberCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcBomberCombatBehavior::OrcBomberCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

OrcBomberCombatBehavior::~OrcBomberCombatBehavior()
{
}

void OrcBomberCombatBehavior::initializePositions()
{
}

void OrcBomberCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(DropTimeBomb::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::VeryCommon));
		attackBehavior->registerAttack(ThrowFlamingWeapon::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeedVerySlow, PlatformerAttack::Priority::Reasonable));
		attackBehavior->registerAttack(BasicSlash::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
	});
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			// inventory->forceInsert(IncrementHealthFlask::create());
		}
	});
}
