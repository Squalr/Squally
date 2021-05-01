#include "GeckyCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Combat/Gecky/GeckyAttackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyManaBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Inventory/HelperInventoryRedirectBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

using namespace cocos2d;

const std::string GeckyCombatBehaviorGroup::MapKey = "gecky-combat";

GeckyCombatBehaviorGroup* GeckyCombatBehaviorGroup::create(GameObject* owner)
{
	GeckyCombatBehaviorGroup* instance = new GeckyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GeckyCombatBehaviorGroup::GeckyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityInventoryBehavior::create(owner),
	HelperInventoryRedirectBehavior::create(owner),
	GeckyAttackBehavior::create(owner),
	GeckyEqBehavior::create(owner),
	GeckyHealthBehavior::create(owner),
	GeckyManaBehavior::create(owner),
	})
{
}

GeckyCombatBehaviorGroup::~GeckyCombatBehaviorGroup()
{
}

void GeckyCombatBehaviorGroup::onLoad()
{
	super::onLoad();
}

void GeckyCombatBehaviorGroup::onDisable()
{
	super::onDisable();
}
