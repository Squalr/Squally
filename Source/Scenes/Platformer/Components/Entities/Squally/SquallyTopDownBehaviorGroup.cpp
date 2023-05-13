#include "SquallyTopDownBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Helpers/HelperManagerBehavior.h"
#include "Scenes/Platformer/Components/Entities/Helpers/Scrappy/ScrappyManagerBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Abilities/SquallyAbilityBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Squally/Camera/SquallyCameraFollowBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Collision/SquallyCollisionBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Squally/Hud/SquallyHudTrackBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Inventory/SquallyDefaultInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Inventory/SquallyInventoryBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Inventory/SquallyReceiveItemBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Misc/SquallyStaticHelpBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Movement/SquallyRespawnBehavior.h"
#include "Scenes/Platformer/Components/Entities/Squally/Stats/SquallyStatsBehaviorGroup.h"
#include "Scenes/Platformer/Components/Entities/Squally/Visual/SquallyVisualBehaviorGroup.h"

using namespace cocos2d;

const std::string SquallyTopDownBehaviorGroup::MapKey = "squally-topdown";

SquallyTopDownBehaviorGroup* SquallyTopDownBehaviorGroup::create(GameObject* owner)
{
	SquallyTopDownBehaviorGroup* instance = new SquallyTopDownBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyTopDownBehaviorGroup::SquallyTopDownBehaviorGroup(GameObject* owner) : super(owner, {
	EntityBehaviorGroup::create(owner),
	SquallyAbilityBehaviorGroup::create(owner),
	SquallyCameraFollowBehavior::create(owner),
	SquallyCollisionBehaviorGroup::create(owner),
	SquallyInventoryBehavior::create(owner),
	SquallyDefaultInventoryBehavior::create(owner),
	SquallyHudTrackBehavior::create(owner),
	SquallyMovementBehavior::create(owner),
	SquallyRespawnBehavior::create(owner),
	SquallyStatsBehaviorGroup::create(owner),
	SquallyVisualBehaviorGroup::create(owner),
	ScrappyManagerBehavior::create(owner),
	SquallyStaticHelpBehavior::create(owner)
	})
{
}

SquallyTopDownBehaviorGroup::~SquallyTopDownBehaviorGroup()
{
}

void SquallyTopDownBehaviorGroup::onLoad()
{
}
