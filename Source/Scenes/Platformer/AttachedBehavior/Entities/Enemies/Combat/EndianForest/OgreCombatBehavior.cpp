#include "OgreCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OgreCombatBehavior::MapKeyAttachedBehavior = "ogre-combat";

OgreCombatBehavior* OgreCombatBehavior::create(GameObject* owner)
{
	OgreCombatBehavior* instance = new OgreCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OgreCombatBehavior::OgreCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

OgreCombatBehavior::~OgreCombatBehavior()
{
}

void OgreCombatBehavior::initializePositions()
{
}

void OgreCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(BasicSlash::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityCommon));
	});
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(IncrementHealthFlask::create());
		}
	});
}
