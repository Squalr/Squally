#include "MedusaCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/ArrowRain/CastArrowRain.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/DoubleSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string MedusaCombatBehavior::MapKey = "medusa-combat";

MedusaCombatBehavior* MedusaCombatBehavior::create(GameObject* owner)
{
	MedusaCombatBehavior* instance = new MedusaCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

MedusaCombatBehavior::MedusaCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.15f);
}

MedusaCombatBehavior::~MedusaCombatBehavior()
{
}

void MedusaCombatBehavior::initializePositions()
{
}

void MedusaCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastArrowRain::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed, EntityResources::Enemies_UnderflowRuins_Medusa_ARROW));
		attackBehavior->registerAttack(DoubleSlash::create(4, 6, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common, 1.0f));
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
