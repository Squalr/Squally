#include "FriendlyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Collision/FriendlyCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Friendly/Collision/FriendlyPlayerCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"

using namespace cocos2d;

const std::string FriendlyBehaviorGroup::MapKey = "friendly";

FriendlyBehaviorGroup* FriendlyBehaviorGroup::create(GameObject* owner)
{
	FriendlyBehaviorGroup* instance = new FriendlyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FriendlyBehaviorGroup::FriendlyBehaviorGroup(GameObject* owner) : super(owner, {
	EntityBehaviorGroup::create(owner),
	EntityInventoryBehavior::create(owner),
	FriendlyCollisionBehavior::create(owner),
	FriendlyPlayerCollisionBehavior::create(owner),
	})
{
}

FriendlyBehaviorGroup::~FriendlyBehaviorGroup()
{
}

void FriendlyBehaviorGroup::onLoad()
{
}
