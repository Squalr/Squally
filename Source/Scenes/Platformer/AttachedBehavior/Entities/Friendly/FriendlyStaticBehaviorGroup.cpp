#include "FriendlyStaticBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Dialogue/EntityDialogueBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Collision/FriendlyCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/NpcCollisionBehavior.h"

using namespace cocos2d;

const std::string FriendlyStaticBehaviorGroup::MapKeyAttachedBehavior = "friendly-static";

FriendlyStaticBehaviorGroup* FriendlyStaticBehaviorGroup::create(GameObject* owner)
{
	FriendlyStaticBehaviorGroup* instance = new FriendlyStaticBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

FriendlyStaticBehaviorGroup::FriendlyStaticBehaviorGroup(GameObject* owner) : super(owner, {
	EntityDialogueBehavior::create(owner),
	EntityBehaviorGroup::create(owner),
	NpcCollisionBehavior::create(owner),
	})
{
}

FriendlyStaticBehaviorGroup::~FriendlyStaticBehaviorGroup()
{
}

void FriendlyStaticBehaviorGroup::onLoad()
{
}
