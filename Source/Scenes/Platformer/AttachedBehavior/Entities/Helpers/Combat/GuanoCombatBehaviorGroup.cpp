#include "GuanoCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Combat/GuanoAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Guano/GuanoManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Inventory/HelperInventoryRedirectBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"

using namespace cocos2d;

const std::string GuanoCombatBehaviorGroup::MapKey = "guano-combat";

GuanoCombatBehaviorGroup* GuanoCombatBehaviorGroup::create(GameObject* owner)
{
	GuanoCombatBehaviorGroup* instance = new GuanoCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GuanoCombatBehaviorGroup::GuanoCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityInventoryBehavior::create(owner),
	HelperInventoryRedirectBehavior::create(owner),
	GuanoAttackBehavior::create(owner),
	GuanoEqBehavior::create(owner),
	GuanoHealthBehavior::create(owner),
	GuanoManaBehavior::create(owner),
	})
{
}

GuanoCombatBehaviorGroup::~GuanoCombatBehaviorGroup()
{
}

void GuanoCombatBehaviorGroup::onLoad()
{
}

void GuanoCombatBehaviorGroup::onDisable()
{
	super::onDisable();
}
