#include "OrcSwordsmanCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcSwordsmanCombatBehavior::MapKeyAttachedBehavior = "orc-swordsman";

OrcSwordsmanCombatBehavior* OrcSwordsmanCombatBehavior::create(GameObject* owner)
{
	OrcSwordsmanCombatBehavior* instance = new OrcSwordsmanCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcSwordsmanCombatBehavior::OrcSwordsmanCombatBehavior(GameObject* owner) : super(owner)
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

OrcSwordsmanCombatBehavior::~OrcSwordsmanCombatBehavior()
{
}

void OrcSwordsmanCombatBehavior::initializePositions()
{
}

void OrcSwordsmanCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(Slash::create(0.7f, 0.2f));
	});
}
