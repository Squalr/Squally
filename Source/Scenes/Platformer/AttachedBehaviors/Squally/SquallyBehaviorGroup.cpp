#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyEquipmentVisualBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyEyeBlinkBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyIsAliveHackBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyMovementBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyOutOfCombatAttackBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyRuneBehaviors.h"

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
