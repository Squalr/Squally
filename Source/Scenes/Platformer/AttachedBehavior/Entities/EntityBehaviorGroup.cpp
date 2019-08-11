#include "EntityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDebugBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

using namespace cocos2d;

const std::string EntityBehaviorGroup::MapKeyAttachedBehavior = "entity";

EntityBehaviorGroup* EntityBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityBehaviorGroup* instance = new EntityBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityBehaviorGroup::EntityBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityCollisionBehaviorGroup::create(owner, attachedBehaviorArgs),
	EntityDebugBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

EntityBehaviorGroup::~EntityBehaviorGroup()
{
}

void EntityBehaviorGroup::onLoad()
{
}
