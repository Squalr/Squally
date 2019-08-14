#include "EntityBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDebugBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

using namespace cocos2d;

const std::string EntityBehaviorGroup::MapKeyAttachedBehavior = "entity";

EntityBehaviorGroup* EntityBehaviorGroup::create(GameObject* owner)
{
	EntityBehaviorGroup* instance = new EntityBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityBehaviorGroup::EntityBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCinematicHijackBehavior::create(owner),
	EntityCollisionBehaviorGroup::create(owner),
	EntityDebugBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	})
{
}

EntityBehaviorGroup::~EntityBehaviorGroup()
{
}

void EntityBehaviorGroup::onLoad()
{
}
