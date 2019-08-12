#include "EntityCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntitySelectionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDebugBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

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
	EntityDebugBehavior::create(owner, attachedBehaviorArgs),
	EntityStatsBehaviorGroup::create(owner, attachedBehaviorArgs),
	})
{
}

EntityCombatBehaviorGroup::~EntityCombatBehaviorGroup()
{
}

void EntityCombatBehaviorGroup::onLoad()
{
}
