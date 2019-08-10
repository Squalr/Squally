#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Abilities/SquallyIsAliveHackBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Abilities/SquallyOutOfCombatAttackBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Collision/SquallyCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Movement/SquallyMovementBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Stats/SquallyEqBehavior.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Stats/SquallyManaBehavior.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Stats/SquallyRuneBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Visual/SquallyEquipmentVisualBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/Visual/SquallyEyeBlinkBehaviors.h"

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
	SquallyCollisionBehaviors::create(owner, attachedBehaviorArgs),
	SquallyEquipmentVisualBehaviors::create(owner, attachedBehaviorArgs),
	SquallyEyeBlinkBehaviors::create(owner, attachedBehaviorArgs),
	SquallyIsAliveHackBehaviors::create(owner, attachedBehaviorArgs),
	SquallyMovementBehaviors::create(owner, attachedBehaviorArgs),
	SquallyOutOfCombatAttackBehaviors::create(owner, attachedBehaviorArgs),
	SquallyManaBehavior::create(owner, attachedBehaviorArgs),
	SquallyEqBehavior::create(owner, attachedBehaviorArgs),
	SquallyRuneBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

SquallyBehaviorGroup::~SquallyBehaviorGroup()
{
}

void SquallyBehaviorGroup::onLoad()
{
}
