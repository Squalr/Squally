#include "SquallyStatsBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyRuneBehavior.h"

using namespace cocos2d;

const std::string SquallyStatsBehaviorGroup::MapKeyAttachedBehavior = "squally-stats";

SquallyStatsBehaviorGroup* SquallyStatsBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyStatsBehaviorGroup* instance = new SquallyStatsBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyStatsBehaviorGroup::SquallyStatsBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	SquallyEqBehavior::create(owner, attachedBehaviorArgs),
	SquallyHealthBehavior::create(owner, attachedBehaviorArgs),
	SquallyManaBehavior::create(owner, attachedBehaviorArgs),
	SquallyRuneBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

SquallyStatsBehaviorGroup::~SquallyStatsBehaviorGroup()
{
}

void SquallyStatsBehaviorGroup::onLoad()
{
}
