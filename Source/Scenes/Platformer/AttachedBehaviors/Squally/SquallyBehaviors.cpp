#include "SquallyBehaviors.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/EntityBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyEquipmentVisualBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyEyeBlinkBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyIsAliveHackBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyMovementBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Squally/SquallyOutOfCombatAttackBehaviors.h"

using namespace cocos2d;

const std::string SquallyBehaviors::MapKeyAttachedBehavior = "squally";

SquallyBehaviors* SquallyBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	SquallyBehaviors* instance = new SquallyBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

SquallyBehaviors::SquallyBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityBehaviors::create(owner, attachedBehaviorArgs),
	SquallyCollisionBehaviors::create(owner, attachedBehaviorArgs),
	SquallyEquipmentVisualBehaviors::create(owner, attachedBehaviorArgs),
	SquallyEyeBlinkBehaviors::create(owner, attachedBehaviorArgs),
	SquallyIsAliveHackBehaviors::create(owner, attachedBehaviorArgs),
	SquallyMovementBehaviors::create(owner, attachedBehaviorArgs),
	SquallyOutOfCombatAttackBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

SquallyBehaviors::~SquallyBehaviors()
{
}

void SquallyBehaviors::onLoad()
{
}
