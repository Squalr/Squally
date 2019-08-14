#include "SquallyVisualBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEquipmentVisualBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Squally/Visual/SquallyEyeBlinkBehavior.h"

using namespace cocos2d;

const std::string SquallyVisualBehaviorGroup::MapKeyAttachedBehavior = "squally-visual-group";

SquallyVisualBehaviorGroup* SquallyVisualBehaviorGroup::create(GameObject* owner)
{
	SquallyVisualBehaviorGroup* instance = new SquallyVisualBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

SquallyVisualBehaviorGroup::SquallyVisualBehaviorGroup(GameObject* owner) : super(owner, {
	SquallyEquipmentVisualBehavior::create(owner),
	SquallyEyeBlinkBehavior::create(owner),
	})
{
}

SquallyVisualBehaviorGroup::~SquallyVisualBehaviorGroup()
{
}

void SquallyVisualBehaviorGroup::onLoad()
{
}
