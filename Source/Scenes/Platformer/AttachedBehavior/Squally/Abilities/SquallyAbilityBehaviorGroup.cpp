#include "SquallyAbilityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyIsAliveHackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyOutOfCombatAttackBehavior.h"

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
	SquallyOutOfCombatAttackBehavior::create(owner),
	})
{
}

SquallyAbilityBehaviorGroup::~SquallyAbilityBehaviorGroup()
{
}

void SquallyAbilityBehaviorGroup::onLoad()
{
}
