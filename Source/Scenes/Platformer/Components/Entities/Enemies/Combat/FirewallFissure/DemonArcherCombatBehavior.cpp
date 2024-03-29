#include "DemonArcherCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/ArrowVolley/CastArrowVolley.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"

#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string DemonArcherCombatBehavior::MapKey = "demon-archer-combat";

DemonArcherCombatBehavior* DemonArcherCombatBehavior::create(GameObject* owner)
{
	DemonArcherCombatBehavior* instance = new DemonArcherCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

DemonArcherCombatBehavior::DemonArcherCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

DemonArcherCombatBehavior::~DemonArcherCombatBehavior()
{
}

void DemonArcherCombatBehavior::initializePositions()
{
}

void DemonArcherCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastArrowVolley::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed, EntityResources::Enemies_FirewallFissure_DemonArcher_ARROW));
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
