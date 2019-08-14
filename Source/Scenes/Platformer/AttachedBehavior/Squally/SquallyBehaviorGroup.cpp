#include "SquallyBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyIsAliveHackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Abilities/SquallyOutOfCombatAttackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Collision/SquallyCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Collision/SquallyWeaponCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Movement/SquallyMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Stats/SquallyStatsBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEquipmentVisualBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEyeBlinkBehavior.h"

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
	SquallyCollisionBehavior::create(owner),
	SquallyWeaponCollisionBehavior::create(owner),
	SquallyEquipmentVisualBehavior::create(owner),
	SquallyEyeBlinkBehavior::create(owner),
	SquallyIsAliveHackBehavior::create(owner),
	SquallyMovementBehavior::create(owner),
	SquallyOutOfCombatAttackBehavior::create(owner),
	SquallyStatsBehaviorGroup::create(owner),
	})
{
}

SquallyBehaviorGroup::~SquallyBehaviorGroup()
{
}

void SquallyBehaviorGroup::onLoad()
{
}
