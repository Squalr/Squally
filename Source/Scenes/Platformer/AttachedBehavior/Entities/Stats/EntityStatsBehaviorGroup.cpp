#include "EntityStatsBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityEqBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityRuneBehavior.h"

using namespace cocos2d;

const std::string EntityStatsBehaviorGroup::MapKeyAttachedBehavior = "entity-stats";

EntityStatsBehaviorGroup* EntityStatsBehaviorGroup::create(GameObject* owner)
{
	EntityStatsBehaviorGroup* instance = new EntityStatsBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityStatsBehaviorGroup::EntityStatsBehaviorGroup(GameObject* owner) : super(owner, {
	EntityEqBehavior::create(owner),
	EntityHealthBehavior::create(owner),
	EntityManaBehavior::create(owner),
	EntityRuneBehavior::create(owner),
	})
{
}

EntityStatsBehaviorGroup::~EntityStatsBehaviorGroup()
{
}

void EntityStatsBehaviorGroup::onLoad()
{
}
