#include "FriendlyCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Combat/EntityCombatBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Combat/FriendlyCombatCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Combat/FriendlyExpBarBehavior.h"

using namespace cocos2d;

const std::string FriendlyCombatBehaviorGroup::MapKey = "friendly-combat-group";

FriendlyCombatBehaviorGroup* FriendlyCombatBehaviorGroup::create(GameObject* owner)
{
	FriendlyCombatBehaviorGroup* instance = new FriendlyCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FriendlyCombatBehaviorGroup::FriendlyCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCombatBehaviorGroup::create(owner),
	FriendlyCombatCollisionBehavior::create(owner),
	FriendlyExpBarBehavior::create(owner),
	})
{
}

FriendlyCombatBehaviorGroup::~FriendlyCombatBehaviorGroup()
{
}

void FriendlyCombatBehaviorGroup::onLoad()
{
}
