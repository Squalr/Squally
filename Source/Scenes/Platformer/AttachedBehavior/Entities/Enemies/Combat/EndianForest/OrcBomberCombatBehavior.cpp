#include "OrcBomberCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcBomberCombatBehavior::MapKeyAttachedBehavior = "orc-bomber";

OrcBomberCombatBehavior* OrcBomberCombatBehavior::create(GameObject* owner)
{
	OrcBomberCombatBehavior* instance = new OrcBomberCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcBomberCombatBehavior::OrcBomberCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->entity->getAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
		{
			Inventory* inventory = entityInventoryBehavior->getInventory();

			if (inventory != nullptr)
			{
				inventory->forceInsert(RestorePotion::create());
			}
		});
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
		attackBehavior->registerAttack(Slash::create(0.7f, 0.2f));
	});
}
