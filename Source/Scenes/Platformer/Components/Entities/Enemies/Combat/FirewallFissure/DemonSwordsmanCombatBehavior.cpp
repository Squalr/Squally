#include "DemonSwordsmanCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Buffs/ScaldingBlade/CastScaldingBlade.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/SuperiorHealthFlask/SuperiorHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string DemonSwordsmanCombatBehavior::MapKey = "demon-swordsman-combat";

DemonSwordsmanCombatBehavior* DemonSwordsmanCombatBehavior::create(GameObject* owner)
{
	DemonSwordsmanCombatBehavior* instance = new DemonSwordsmanCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

DemonSwordsmanCombatBehavior::DemonSwordsmanCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.25f);
}

DemonSwordsmanCombatBehavior::~DemonSwordsmanCombatBehavior()
{
}

void DemonSwordsmanCombatBehavior::initializePositions()
{
}

void DemonSwordsmanCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(CastScaldingBlade::create(0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Guaranteed));
		attackBehavior->registerAttack(BasicSlash::create(8, 10, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(SuperiorHealthFlask::create());
		}
	});
}
