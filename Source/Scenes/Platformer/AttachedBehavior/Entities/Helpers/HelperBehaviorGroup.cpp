#include "HelperBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/EntityBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Collision/HelperCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Helpers/Inventory/HelperInventoryRedirectBehavior.h"

using namespace cocos2d;

const std::string HelperBehaviorGroup::MapKey = "helper";

HelperBehaviorGroup* HelperBehaviorGroup::create(GameObject* owner)
{
	HelperBehaviorGroup* instance = new HelperBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

HelperBehaviorGroup::HelperBehaviorGroup(GameObject* owner) : super(owner, {
	HelperCollisionBehavior::create(owner),
	HelperInventoryRedirectBehavior::create(owner),
	EntityBehaviorGroup::create(owner),
	})
{
}

HelperBehaviorGroup::~HelperBehaviorGroup()
{
}

void HelperBehaviorGroup::onLoad()
{
}

void HelperBehaviorGroup::onDisable()
{
	super::onDisable();
}
