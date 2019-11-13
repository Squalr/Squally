#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/ScrappyManagerBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/HelperManagerBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Abilities/SquallyAbilityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Camera/SquallyCameraFollowBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Collision/SquallyCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Hud/SquallyHudTrackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Items/SquallyDefaultInventoryBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Items/SquallyReceiveItemBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyFloatBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Stats/SquallyStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyVisualBehaviorGroup.h"

using namespace cocos2d;

const std::string SquallyBehaviorGroup::MapKeyAttachedBehavior = "squally";

SquallyBehaviorGroup* SquallyBehaviorGroup::create(GameObject* owner)
{
	SquallyBehaviorGroup* instance = new SquallyBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyBehaviorGroup::SquallyBehaviorGroup(GameObject* owner) : super(owner, {
	EntityBehaviorGroup::create(owner),
	SquallyAbilityBehaviorGroup::create(owner),
	SquallyCameraFollowBehavior::create(owner),
	SquallyCollisionBehaviorGroup::create(owner),
	SquallyDefaultInventoryBehavior::create(owner),
	SquallyHudTrackBehavior::create(owner),
	SquallyReceiveItemBehavior::create(owner),
	SquallyFloatBehavior::create(owner),
	SquallyMovementBehavior::create(owner),
	SquallyStatsBehaviorGroup::create(owner),
	SquallyVisualBehaviorGroup::create(owner),
	ScrappyManagerBehavior::create(owner),
	HelperManagerBehavior::create(owner),
	})
{
}

SquallyBehaviorGroup::~SquallyBehaviorGroup()
{
}

void SquallyBehaviorGroup::onLoad()
{
}
