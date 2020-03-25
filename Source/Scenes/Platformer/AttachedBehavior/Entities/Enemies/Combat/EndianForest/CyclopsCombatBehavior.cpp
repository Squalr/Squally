#include "CyclopsCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/StoneShield/CastStoneShield.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string CyclopsCombatBehavior::MapKey = "cyclops-combat";

CyclopsCombatBehavior* CyclopsCombatBehavior::create(GameObject* owner)
{
	CyclopsCombatBehavior* instance = new CyclopsCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

CyclopsCombatBehavior::CyclopsCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

CyclopsCombatBehavior::~CyclopsCombatBehavior()
{
}

void CyclopsCombatBehavior::initializePositions()
{
}

void CyclopsCombatBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastStoneShield::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});

	this->setTimelineSpeed(1.15f);
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(IncrementHealthFlask::create());
		}
	});
}
