#include "GeckyBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Gecky/GeckyManaBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperFollowMovementBehavior.h"

using namespace cocos2d;

const std::string GeckyBehaviorGroup::MapKey = "gecky";

GeckyBehaviorGroup* GeckyBehaviorGroup::create(GameObject* owner)
{
	GeckyBehaviorGroup* instance = new GeckyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GeckyBehaviorGroup::GeckyBehaviorGroup(GameObject* owner) : super(owner, {
	HelperBehaviorGroup::create(owner),
	GeckyEqBehavior::create(owner),
	GeckyHealthBehavior::create(owner),
	GeckyManaBehavior::create(owner),
	HelperFollowMovementBehavior::create(owner),
	})
{
}

GeckyBehaviorGroup::~GeckyBehaviorGroup()
{
}

void GeckyBehaviorGroup::onLoad()
{
}
