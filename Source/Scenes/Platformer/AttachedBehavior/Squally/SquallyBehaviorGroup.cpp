#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyIsAliveHackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyOutOfCombatAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Collision/SquallyCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyRuneBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEquipmentVisualBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEyeBlinkBehavior.h"

using namespace cocos2d;

const std::string SquallyBehaviorGroup::MapKeyAttachedBehavior = "squally";

SquallyBehaviorGroup* SquallyBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyBehaviorGroup* instance = new SquallyBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyBehaviorGroup::SquallyBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityBehaviorGroup::create(owner, attachedBehaviorArgs),
	SquallyCollisionBehavior::create(owner, attachedBehaviorArgs),
	SquallyEquipmentVisualBehavior::create(owner, attachedBehaviorArgs),
	SquallyEyeBlinkBehavior::create(owner, attachedBehaviorArgs),
	SquallyIsAliveHackBehavior::create(owner, attachedBehaviorArgs),
	SquallyMovementBehavior::create(owner, attachedBehaviorArgs),
	SquallyOutOfCombatAttackBehavior::create(owner, attachedBehaviorArgs),
	SquallyManaBehavior::create(owner, attachedBehaviorArgs),
	SquallyEqBehavior::create(owner, attachedBehaviorArgs),
	SquallyRuneBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

SquallyBehaviorGroup::~SquallyBehaviorGroup()
{
}

void SquallyBehaviorGroup::onLoad()
{
}
