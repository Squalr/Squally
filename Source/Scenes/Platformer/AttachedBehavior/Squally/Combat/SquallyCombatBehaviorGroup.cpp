#include "SquallyCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Combat/SquallyAttackBehavior.h"

using namespace cocos2d;

const std::string SquallyCombatBehaviorGroup::MapKeyAttachedBehavior = "squally-combat-group";

SquallyCombatBehaviorGroup* SquallyCombatBehaviorGroup::create(GameObject* owner)
{
	SquallyCombatBehaviorGroup* instance = new SquallyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyCombatBehaviorGroup::SquallyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCombatBehaviorGroup::create(owner),
	SquallyAttackBehavior::create(owner),
	})
{
}

SquallyCombatBehaviorGroup::~SquallyCombatBehaviorGroup()
{
}

void SquallyCombatBehaviorGroup::onLoad()
{
}
