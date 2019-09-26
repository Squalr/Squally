#include "OrcGruntCombatBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Consumables/Health/ThrowRestorePotion.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcGruntCombatBehavior::MapKeyAttachedBehavior = "orc-grunt";

OrcGruntCombatBehavior* OrcGruntCombatBehavior::create(GameObject* owner)
{
	OrcGruntCombatBehavior* instance = new OrcGruntCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcGruntCombatBehavior::OrcGruntCombatBehavior(GameObject* owner) : super(owner)
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

OrcGruntCombatBehavior::~OrcGruntCombatBehavior()
{
}

void OrcGruntCombatBehavior::initializePositions()
{
}

void OrcGruntCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(Slash::create(0.7f, 0.2f));
	});
}
