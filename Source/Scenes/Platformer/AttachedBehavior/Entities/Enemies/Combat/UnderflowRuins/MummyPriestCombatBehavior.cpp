#include "MummyPriestCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityBuffBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Undying/UndyingAutoCast.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Reflect/CastReflect.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string MummyPriestCombatBehavior::MapKey = "mummy-priest-combat";

MummyPriestCombatBehavior* MummyPriestCombatBehavior::create(GameObject* owner)
{
	MummyPriestCombatBehavior* instance = new MummyPriestCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

MummyPriestCombatBehavior::MummyPriestCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeed(1.25f);
}

MummyPriestCombatBehavior::~MummyPriestCombatBehavior()
{
}

void MummyPriestCombatBehavior::initializePositions()
{
}

void MummyPriestCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastReflect::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(4, 6, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::IfNecessary));
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
