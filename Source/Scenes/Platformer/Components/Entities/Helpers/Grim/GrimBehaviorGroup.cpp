#include "GrimBehaviorGroup.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimEqBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimHealthBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimManaBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Grim/GrimSoulHarvestBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperFollowMovementBehavior.h"

using namespace cocos2d;

const std::string GrimBehaviorGroup::MapKey = "grim";

GrimBehaviorGroup* GrimBehaviorGroup::create(GameObject* owner)
{
	GrimBehaviorGroup* instance = new GrimBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

GrimBehaviorGroup::GrimBehaviorGroup(GameObject* owner) : super(owner, {
	HelperBehaviorGroup::create(owner),
	GrimEqBehavior::create(owner),
	GrimHealthBehavior::create(owner),
	GrimManaBehavior::create(owner),
	GrimSoulHarvestBehavior::create(owner),
	HelperFollowMovementBehavior::create(owner),
	})
{
}

GrimBehaviorGroup::~GrimBehaviorGroup()
{
}

void GrimBehaviorGroup::onLoad()
{
}
