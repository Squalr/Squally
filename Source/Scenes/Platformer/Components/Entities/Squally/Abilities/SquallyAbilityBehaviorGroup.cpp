#include "SquallyAbilityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Squally/Abilities/IsSwimming/SquallySwimHackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Abilities/SquallyDisableHackFxBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Abilities/SquallyHackingBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Abilities/SquallyOutOfCombatAttackBehavior.h"

using namespace cocos2d;

const std::string SquallyAbilityBehaviorGroup::MapKey = "squally-ability-group";

SquallyAbilityBehaviorGroup* SquallyAbilityBehaviorGroup::create(GameObject* owner)
{
	SquallyAbilityBehaviorGroup* instance = new SquallyAbilityBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyAbilityBehaviorGroup::SquallyAbilityBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyDisableHackFxBehavior::create(owner),
	SquallyHackingBehavior::create(owner),
	SquallyOutOfCombatAttackBehavior::create(owner),
	SquallySwimHackBehavior::create(owner),
	})
{
}

SquallyAbilityBehaviorGroup::~SquallyAbilityBehaviorGroup()
{
}

void SquallyAbilityBehaviorGroup::onLoad()
{
}
