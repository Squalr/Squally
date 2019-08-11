#include "EntityCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviorGroup::MapKeyAttachedBehavior = "entity-collisions";

EntityCollisionBehaviorGroup* EntityCollisionBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCollisionBehaviorGroup* instance = new EntityCollisionBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviorGroup::EntityCollisionBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityGroundCollisionBehavior::create(owner, attachedBehaviorArgs),
	EntityMovementCollisionBehavior::create(owner, attachedBehaviorArgs),
	EntityWeaponCollisionBehavior::create(owner, attachedBehaviorArgs),
	})
{
}

EntityCollisionBehaviorGroup::~EntityCollisionBehaviorGroup()
{
}

void EntityCollisionBehaviorGroup::onLoad()
{
}
