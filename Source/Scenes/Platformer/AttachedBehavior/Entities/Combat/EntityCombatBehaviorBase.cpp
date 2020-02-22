#include "EntityCombatBehaviorBase.h"

#include "Engine/Inventory/Inventory.h"
#include "Engine/Inventory/Item.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Items/EntityInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityAttackBehavior.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Weapons/Slash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/RestorePotion/RestorePotion.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

EntityCombatBehaviorBase::EntityCombatBehaviorBase(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->timelineSpeed = 1.0f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityCombatBehaviorBase::~EntityCombatBehaviorBase()
{
}

void EntityCombatBehaviorBase::setTimelineSpeed(float timelineSpeed)
{
	this->timelineSpeed = timelineSpeed;
}

float EntityCombatBehaviorBase::getTimelineSpeed()
{
	return this->timelineSpeed;
}

void EntityCombatBehaviorBase::onLoad()
{
}
