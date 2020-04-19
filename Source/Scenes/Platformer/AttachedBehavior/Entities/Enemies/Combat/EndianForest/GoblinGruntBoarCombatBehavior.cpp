#include "GoblinGruntBoarCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Haste/CastHaste.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string GoblinGruntBoarCombatBehavior::MapKey = "goblin-grunt-boar-combat";

GoblinGruntBoarCombatBehavior* GoblinGruntBoarCombatBehavior::create(GameObject* owner)
{
	GoblinGruntBoarCombatBehavior* instance = new GoblinGruntBoarCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

GoblinGruntBoarCombatBehavior::GoblinGruntBoarCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeed(1.15f);
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
		attackBehavior->registerAttack(CastHaste::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
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
