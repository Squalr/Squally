#include "SquallyCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Scrappy/Combat/ScrappyCombatManagerBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Abilities/SquallyHackingBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Combat/SquallyAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Items/SquallyReceiveItemBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyFloatBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyVisualBehaviorGroup.h"

using namespace cocos2d;

const std::string SquallyCombatBehaviorGroup::MapKeyAttachedBehavior = "squally-combat";

SquallyCombatBehaviorGroup* SquallyCombatBehaviorGroup::create(GameObject* owner)
{
	SquallyCombatBehaviorGroup* instance = new SquallyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyCombatBehaviorGroup::SquallyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCombatBehaviorGroup::create(owner),
	ScrappyCombatManagerBehavior::create(owner),
	SquallyHackingBehavior::create(owner),
	SquallyAttackBehavior::create(owner),
	SquallyFloatBehavior::create(owner),
	SquallyStatsBehaviorGroup::create(owner),
	SquallyVisualBehaviorGroup::create(owner),
	SquallyReceiveItemBehavior::create(owner),
	})
{
}

SquallyCombatBehaviorGroup::~SquallyCombatBehaviorGroup()
{
}

void SquallyCombatBehaviorGroup::onLoad()
{
}

void SquallyCombatBehaviorGroup::onDisable()
{
	super::onDisable();
}
