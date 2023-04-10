#include "LavaGolemCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Debuffs/Enflame/CastEnflame.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string LavaGolemCombatBehavior::MapKey = "lava-golem-combat";

LavaGolemCombatBehavior* LavaGolemCombatBehavior::create(GameObject* owner)
{
	LavaGolemCombatBehavior* instance = new LavaGolemCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

LavaGolemCombatBehavior::LavaGolemCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

LavaGolemCombatBehavior::~LavaGolemCombatBehavior()
{
}

void LavaGolemCombatBehavior::initializePositions()
{
}

void LavaGolemCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastEnflame::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(8, 10, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
		}
	});
}
