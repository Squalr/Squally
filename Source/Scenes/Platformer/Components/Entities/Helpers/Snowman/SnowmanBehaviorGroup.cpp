#include "SnowmanBehaviorGroup.h"

#include "Scenes/Platformer/Components/Entities/Helpers/HelperBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperFollowMovementBehavior.h"

using namespace cocos2d;

const std::string SnowmanBehaviorGroup::MapKey = "snowman";

SnowmanBehaviorGroup* SnowmanBehaviorGroup::create(GameObject* owner)
{
	SnowmanBehaviorGroup* instance = new SnowmanBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SnowmanBehaviorGroup::SnowmanBehaviorGroup(GameObject* owner) : super(owner, {
	HelperBehaviorGroup::create(owner),
	HelperFollowMovementBehavior::create(owner),
	})
{
}

SnowmanBehaviorGroup::~SnowmanBehaviorGroup()
{
}

void SnowmanBehaviorGroup::onLoad()
{
}

void SnowmanBehaviorGroup::onDisable()
{
	super::onDisable();
}
