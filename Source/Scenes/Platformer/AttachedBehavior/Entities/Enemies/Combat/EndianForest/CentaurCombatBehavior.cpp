#include "CentaurCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string CentaurCombatBehavior::MapKeyAttachedBehavior = "centaur";

CentaurCombatBehavior* CentaurCombatBehavior::create(GameObject* owner)
{
	CentaurCombatBehavior* instance = new CentaurCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

CentaurCombatBehavior::CentaurCombatBehavior(GameObject* owner) : super(owner)
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

CentaurCombatBehavior::~CentaurCombatBehavior()
{
}

void CentaurCombatBehavior::initializePositions()
{
}

void CentaurCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(Slash::create(0.7f, 0.2f));
	});
}
