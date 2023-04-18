#include "GrimCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Combat/Grim/GrimAttackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimManaBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Inventory/HelperInventoryRedirectBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

using namespace cocos2d;

const std::string GrimCombatBehaviorGroup::MapKey = "grim-combat";

GrimCombatBehaviorGroup* GrimCombatBehaviorGroup::create(GameObject* owner)
{
	GrimCombatBehaviorGroup* instance = new GrimCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GrimCombatBehaviorGroup::GrimCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityInventoryBehavior::create(owner),
	HelperInventoryRedirectBehavior::create(owner),
	GrimAttackBehavior::create(owner),
	GrimEqBehavior::create(owner),
	GrimHealthBehavior::create(owner),
	GrimManaBehavior::create(owner),
	})
{
}

GrimCombatBehaviorGroup::~GrimCombatBehaviorGroup()
{
}

void GrimCombatBehaviorGroup::onLoad()
{
	super::onLoad();
}

void GrimCombatBehaviorGroup::onDisable()
{
	super::onDisable();
}
