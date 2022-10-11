#include "GuanoPetrifiedBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityDisableCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Guano/GuanoEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Guano/GuanoHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Guano/GuanoManaBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/GuanoPetrified/RopedMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperFollowMovementBehavior.h"

using namespace cocos2d;

const std::string GuanoPetrifiedBehaviorGroup::MapKey = "guano-petrified";

GuanoPetrifiedBehaviorGroup* GuanoPetrifiedBehaviorGroup::create(GameObject* owner)
{
	GuanoPetrifiedBehaviorGroup* instance = new GuanoPetrifiedBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GuanoPetrifiedBehaviorGroup::GuanoPetrifiedBehaviorGroup(GameObject* owner) : super(owner, {
	HelperBehaviorGroup::create(owner),
	GuanoEqBehavior::create(owner),
	GuanoHealthBehavior::create(owner),
	GuanoManaBehavior::create(owner),
	HelperFollowMovementBehavior::create(owner),
	RopedMovementBehavior::create(owner),
	EntityDisableCollisionBehavior::create(owner),
	})
{
}

GuanoPetrifiedBehaviorGroup::~GuanoPetrifiedBehaviorGroup()
{
}

void GuanoPetrifiedBehaviorGroup::onLoad()
{
}
