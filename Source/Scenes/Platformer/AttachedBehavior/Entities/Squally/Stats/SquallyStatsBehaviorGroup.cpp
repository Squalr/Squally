#include "SquallyStatsBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyRuneBehavior.h"

using namespace cocos2d;

const std::string SquallyStatsBehaviorGroup::MapKey = "squally-stats-group";

SquallyStatsBehaviorGroup* SquallyStatsBehaviorGroup::create(GameObject* owner)
{
	SquallyStatsBehaviorGroup* instance = new SquallyStatsBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyStatsBehaviorGroup::SquallyStatsBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyEqBehavior::create(owner),
	SquallyHealthBehavior::create(owner),
	SquallyManaBehavior::create(owner),
	SquallyRuneBehavior::create(owner),
	})
{
}

SquallyStatsBehaviorGroup::~SquallyStatsBehaviorGroup()
{
}

void SquallyStatsBehaviorGroup::onLoad()
{
}
