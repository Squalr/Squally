#include "GoblinGruntBoarCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string GoblinGruntBoarCombatBehavior::MapKeyAttachedBehavior = "goblin-grunt-boar";

GoblinGruntBoarCombatBehavior* GoblinGruntBoarCombatBehavior::create(GameObject* owner)
{
	GoblinGruntBoarCombatBehavior* instance = new GoblinGruntBoarCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

GoblinGruntBoarCombatBehavior::GoblinGruntBoarCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEnemy*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		Inventory* inventory = this->entity->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(RestorePotion::create());
		}
	}
}

GoblinGruntBoarCombatBehavior::~GoblinGruntBoarCombatBehavior()
{
}

void GoblinGruntBoarCombatBehavior::initializePositions()
{
}

void GoblinGruntBoarCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(Slash::create(0.7f, 0.2f));
	});
}
