#include "GuanoAttackBehavior.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Enemies/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/IncrementHealthFlask/IncrementHealthFlask.h"

#include "Resources/UIResources.h"

using namespace cocos2d;
	
const std::string GuanoAttackBehavior::MapKey = "guano-attack";

GuanoAttackBehavior* GuanoAttackBehavior::create(GameObject* owner)
{
	GuanoAttackBehavior* instance = new GuanoAttackBehavior(owner);

	instance->autorelease();

	return instance;
}

GuanoAttackBehavior::GuanoAttackBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

GuanoAttackBehavior::~GuanoAttackBehavior()
{
}

void GuanoAttackBehavior::initializePositions()
{
}

void GuanoAttackBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityAttackBehavior>([=](EntityAttackBehavior* attackBehavior)
	{
		std::tuple<int, int> attackRange = attackBehavior->computeAttackRange();
		int minAttack = std::get<0>(attackRange);
		int maxAttack = std::get<1>(attackRange);

		attackBehavior->registerAttack(BasicSlash::create(minAttack, maxAttack, 0.7f, EntityAttackBehavior::DefaultRecoverSpeed, PlatformerAttack::Priority::Common));
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

void GuanoAttackBehavior::onDisable()
{
	super::onDisable();
}
