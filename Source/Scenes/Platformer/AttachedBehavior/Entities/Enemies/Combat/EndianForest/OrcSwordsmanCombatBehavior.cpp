#include "OrcSwordsmanCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Entities/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/ThrowWeapon.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OrcSwordsmanCombatBehavior::MapKey = "orc-swordsman-combat";

OrcSwordsmanCombatBehavior* OrcSwordsmanCombatBehavior::create(GameObject* owner)
{
	OrcSwordsmanCombatBehavior* instance = new OrcSwordsmanCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OrcSwordsmanCombatBehavior::OrcSwordsmanCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
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
		attackBehavior->registerAttack(ThrowWeapon::create(0.55f, EntityAttackBehavior::DefaultRecoverSpeedSlow, PlatformerAttack::PriorityCommon));
		attackBehavior->registerAttack(BasicSlash::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::PriorityUncommon));
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
