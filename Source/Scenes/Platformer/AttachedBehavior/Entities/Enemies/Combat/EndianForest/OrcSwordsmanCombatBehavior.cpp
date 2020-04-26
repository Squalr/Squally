#include "OrcSwordsmanCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/DoubleSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/Flurry.h"
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
	
	this->setTimelineSpeed(1.15f);
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
		attackBehavior->registerAttack(DoubleSlash::create(3, 5, 0.5f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed, 0.1f));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
		
		// attackBehavior->registerAttack(Flurry::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
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
