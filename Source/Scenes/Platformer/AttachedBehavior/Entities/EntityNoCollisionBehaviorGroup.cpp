#include "EntityNoCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Cinematic/EntityCinematicHijackBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Developer/EntityDeveloperBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Movement/EntityMovementBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityStatsBehaviorGroup.h"

using namespace cocos2d;

const std::string EntityNoCollisionBehaviorGroup::MapKeyAttachedBehavior = "entity-no-collision";

EntityNoCollisionBehaviorGroup* EntityNoCollisionBehaviorGroup::create(GameObject* owner)
{
	EntityNoCollisionBehaviorGroup* instance = new EntityNoCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityNoCollisionBehaviorGroup::EntityNoCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityCinematicHijackBehavior::create(owner),
	EntityDeveloperBehavior::create(owner),
	EntityStatsBehaviorGroup::create(owner),
	EntityMovementBehavior::create(owner),
	})
{
}

EntityNoCollisionBehaviorGroup::~EntityNoCollisionBehaviorGroup()
{
}

void EntityNoCollisionBehaviorGroup::onLoad()
{
}
