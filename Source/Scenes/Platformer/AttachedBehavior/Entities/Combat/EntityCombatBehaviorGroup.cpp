#include "EntityCombatBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntitySelectionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDebugBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

using namespace cocos2d;

const std::string EntityCombatBehaviorGroup::MapKeyAttachedBehavior = "entity-collisions";

EntityCombatBehaviorGroup* EntityCombatBehaviorGroup::create(GameObject* owner)
{
	EntityCombatBehaviorGroup* instance = new EntityCombatBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityCombatBehaviorGroup::EntityCombatBehaviorGroup(GameObject* owner) : super(owner, {
	EntitySelectionBehavior::create(owner),
	EntityDebugBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	})
{
}

EntityCombatBehaviorGroup::~EntityCombatBehaviorGroup()
{
}

void EntityCombatBehaviorGroup::onLoad()
{
}
