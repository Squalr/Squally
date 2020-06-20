#include "AnubisPupCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
// #include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Weakness/CastWeakness.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string AnubisPupCombatBehavior::MapKey = "anubis-pup-combat";

AnubisPupCombatBehavior* AnubisPupCombatBehavior::create(GameObject* owner)
{
	AnubisPupCombatBehavior* instance = new AnubisPupCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

AnubisPupCombatBehavior::AnubisPupCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeed(1.15f);
}

AnubisPupCombatBehavior::~AnubisPupCombatBehavior()
{
}

void AnubisPupCombatBehavior::initializePositions()
{
}

void AnubisPupCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		// attackBehavior->registerAttack(CastWeakness::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(4, 6, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
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
