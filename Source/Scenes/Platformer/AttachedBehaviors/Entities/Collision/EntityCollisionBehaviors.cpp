#include "EntityCollisionBehaviors.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityGroundCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityMovementCollisionBehaviors.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviors::MapKeyAttachedBehavior = "entity-collisions";

EntityCollisionBehaviors* EntityCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCollisionBehaviors* instance = new EntityCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviors::EntityCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityGroundCollisionBehaviors::create(owner, attachedBehaviorArgs),
	EntityMovementCollisionBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

EntityCollisionBehaviors::~EntityCollisionBehaviors()
{
}

void EntityCollisionBehaviors::onLoad()
{
}
