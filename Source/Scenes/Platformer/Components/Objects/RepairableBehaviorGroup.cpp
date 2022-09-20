#include "RepairableBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Objects/ObjectSelectionBehavior.h"
#include "Scenes/Platformer/Components/Objects/RepairableBehavior.h"

using namespace cocos2d;

const std::string RepairableBehaviorGroup::MapKey = "repairable";

RepairableBehaviorGroup* RepairableBehaviorGroup::create(GameObject* owner)
{
	RepairableBehaviorGroup* instance = new RepairableBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

RepairableBehaviorGroup::RepairableBehaviorGroup(GameObject* owner) : super(owner, {
	ObjectSelectionBehavior::create(owner),
	RepairableBehavior::create(owner),
	})
{
}

RepairableBehaviorGroup::~RepairableBehaviorGroup()
{
}

void RepairableBehaviorGroup::onLoad()
{
}
