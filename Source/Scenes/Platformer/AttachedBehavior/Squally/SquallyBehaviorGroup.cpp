#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Helpers/HelperManagerBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyAbilityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Collision/SquallyCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyVisualBehaviorGroup.h"

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
	SquallyCollisionBehaviorGroup::create(owner),
	SquallyMovementBehavior::create(owner),
	SquallyStatsBehaviorGroup::create(owner),
	SquallyVisualBehaviorGroup::create(owner),
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
