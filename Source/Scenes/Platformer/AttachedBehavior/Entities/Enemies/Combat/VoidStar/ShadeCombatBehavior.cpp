#include "ShadeCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/Strength/CastStrength.h"
#include "Scenes/Platformer/Level/Combat/Attacks/BaseAttacks/BasicSlash.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string ShadeCombatBehavior::MapKey = "shade-combat";

ShadeCombatBehavior* ShadeCombatBehavior::create(GameObject* owner)
{
	ShadeCombatBehavior* instance = new ShadeCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

ShadeCombatBehavior::ShadeCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

ShadeCombatBehavior::~ShadeCombatBehavior()
{
}

void ShadeCombatBehavior::initializePositions()
{
}

void ShadeCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastStrength::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForAttachedBehavior<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
