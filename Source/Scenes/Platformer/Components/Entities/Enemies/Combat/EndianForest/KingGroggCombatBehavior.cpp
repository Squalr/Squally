#include "KingGroggCombatBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/BasicSlash/BasicSlash.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Abilities/DragonBreath/DragonBreath.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string KingGroggCombatBehavior::MapKey = "king-grogg-combat";

KingGroggCombatBehavior* KingGroggCombatBehavior::create(GameObject* owner)
{
	KingGroggCombatBehavior* instance = new KingGroggCombatBehavior(owner);

	instance->autorelease();

	return instance;
}

KingGroggCombatBehavior::KingGroggCombatBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	
	this->setTimelineSpeedBase(1.35f);
}

KingGroggCombatBehavior::~KingGroggCombatBehavior()
{
}

void KingGroggCombatBehavior::initializePositions()
{
}

void KingGroggCombatBehavior::onLoad()
{
	super::onLoad();
	
	this->entity->watchForComponent<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		attackBehavior->registerAttack(DragonBreath::create(0.5f, EntityAttackBehavior::DefaultRecoverSpeedSlow, PlatformerAttack::Priority::VeryCommon));
		attackBehavior->registerAttack(BasicSlash::create(3, 5, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Rare));
	});
	
	this->entity->watchForComponent<EntityInventoryBehavior>([=](EntityInventoryBehavior* entityInventoryBehavior)
	{
		Inventory* inventory = entityInventoryBehavior->getInventory();

		if (inventory != nullptr)
		{
			inventory->forceInsert(IncrementHealthFlask::create());
		}
	});
}
