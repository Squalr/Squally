#include "SnowmanBehaviorGroup.h"

#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/HelperBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/FollowMovementBehavior.h"

using namespace cocos2d;

const std::string SnowmanBehaviorGroup::MapKeyAttachedBehavior = "snowman";

SnowmanBehaviorGroup* SnowmanBehaviorGroup::create(GameObject* owner)
{
	SnowmanBehaviorGroup* instance = new SnowmanBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SnowmanBehaviorGroup::SnowmanBehaviorGroup(GameObject* owner) : super(owner, {
	HelperBehaviorGroup::create(owner),
	FollowMovementBehavior::create(owner),
	})
{
}

SnowmanBehaviorGroup::~SnowmanBehaviorGroup()
{
}

void SnowmanBehaviorGroup::onLoad()
{
}
