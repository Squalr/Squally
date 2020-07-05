#include "OsirisCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Undying/UndyingAutoCast.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/ManaDrain/CastManaDrain.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string OsirisCombatBehavior::MapKey = "osiris-combat";

OsirisCombatBehavior* OsirisCombatBehavior::create(GameObject* owner)
{
	OsirisCombatBehavior* instance = new OsirisCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

OsirisCombatBehavior::OsirisCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

OsirisCombatBehavior::~OsirisCombatBehavior()
{
}

void OsirisCombatBehavior::initializePositions()
{
}

void OsirisCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastManaDrain::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::VeryCommon));
		attackBehavior->registerAttack(BasicSlash::create(5, 7, 1.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
	});

	this->entity->watchForAttachedBehavior<EntityBuffBehavior>([&](EntityBuffBehavior* entityBuffBehavior)
	{
		entityBuffBehavior->applyBuff(UndyingAutoCast::create(this->entity, this->entity));
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
