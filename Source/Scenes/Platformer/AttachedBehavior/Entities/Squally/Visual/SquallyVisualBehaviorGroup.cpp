#include "SquallyVisualBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyAnimationBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyDeadVisualBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyEquipmentVisualBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyEyeBlinkBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Visual/SquallyMouthBehavior.h"

using namespace cocos2d;

const std::string SquallyVisualBehaviorGroup::MapKeyAttachedBehavior = "squally-visual-group";

SquallyVisualBehaviorGroup* SquallyVisualBehaviorGroup::create(GameObject* owner)
{
	SquallyVisualBehaviorGroup* instance = new SquallyVisualBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyVisualBehaviorGroup::SquallyVisualBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyAnimationBehavior::create(owner),
	SquallyDeadVisualBehavior::create(owner),
	SquallyEquipmentVisualBehavior::create(owner),
	SquallyEyeBlinkBehavior::create(owner),
	SquallyMouthBehavior::create(owner),
	})
{
}

SquallyVisualBehaviorGroup::~SquallyVisualBehaviorGroup()
{
}

void SquallyVisualBehaviorGroup::onLoad()
{
}
