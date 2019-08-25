#include "SquallyAbilityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyIsAliveHackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyHackingBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyOutOfCombatAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallySensingBehavior.h"

using namespace cocos2d;

const std::string SquallyAbilityBehaviorGroup::MapKeyAttachedBehavior = "squally-ability-group";

SquallyAbilityBehaviorGroup* SquallyAbilityBehaviorGroup::create(GameObject* owner)
{
	SquallyAbilityBehaviorGroup* instance = new SquallyAbilityBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyAbilityBehaviorGroup::SquallyAbilityBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyIsAliveHackBehavior::create(owner),
	SquallyHackingBehavior::create(owner),
	SquallyOutOfCombatAttackBehavior::create(owner),
	SquallySensingBehavior::create(owner),
	})
{
}

SquallyAbilityBehaviorGroup::~SquallyAbilityBehaviorGroup()
{
}

void SquallyAbilityBehaviorGroup::onLoad()
{
}
