#include "FriendlyNoCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityNoCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Collision/FriendlyCollisionBehavior.h"

using namespace cocos2d;

const std::string FriendlyNoCollisionBehaviorGroup::MapKey = "friendly-no-collision";

FriendlyNoCollisionBehaviorGroup* FriendlyNoCollisionBehaviorGroup::create(GameObject* owner)
{
	FriendlyNoCollisionBehaviorGroup* instance = new FriendlyNoCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FriendlyNoCollisionBehaviorGroup::FriendlyNoCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityNoCollisionBehaviorGroup::create(owner),
	})
{
}

FriendlyNoCollisionBehaviorGroup::~FriendlyNoCollisionBehaviorGroup()
{
}

void FriendlyNoCollisionBehaviorGroup::onLoad()
{
}
