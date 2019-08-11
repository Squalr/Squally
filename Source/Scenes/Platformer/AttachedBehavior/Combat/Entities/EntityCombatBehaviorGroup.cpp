#include "EntityCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Combat/Entities/EntitySelectionBehavior.h"

using namespace cocos2d;

const std::string EntityCombatBehaviorGroup::MapKeyAttachedBehavior = "entity-collisions";

EntityCombatBehaviorGroup* EntityCombatBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCombatBehaviorGroup* instance = new EntityCombatBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCombatBehaviorGroup::EntityCombatBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntitySelectionBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

EntityCombatBehaviorGroup::~EntityCombatBehaviorGroup()
{
}

void EntityCombatBehaviorGroup::onLoad()
{
}
