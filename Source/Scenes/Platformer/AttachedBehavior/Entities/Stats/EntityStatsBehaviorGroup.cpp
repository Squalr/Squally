#include "EntityStatsBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"

using namespace cocos2d;

const std::string EntityStatsBehaviorGroup::MapKeyAttachedBehavior = "entity-stats";

EntityStatsBehaviorGroup* EntityStatsBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityStatsBehaviorGroup* instance = new EntityStatsBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityStatsBehaviorGroup::EntityStatsBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityEqBehavior::create(owner, attachedBehaviorArgs),
	EntityHealthBehavior::create(owner, attachedBehaviorArgs),
	EntityManaBehavior::create(owner, attachedBehaviorArgs),
	EntityRuneBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

EntityStatsBehaviorGroup::~EntityStatsBehaviorGroup()
{
}

void EntityStatsBehaviorGroup::onLoad()
{
}
