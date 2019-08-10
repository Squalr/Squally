#include "EntityCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityGroundCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityMovementCollisionBehaviors.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityWeaponCollisionBehaviors.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviorGroup::MapKeyAttachedBehavior = "entity-collisions";

EntityCollisionBehaviorGroup* EntityCollisionBehaviorGroup::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCollisionBehaviorGroup* instance = new EntityCollisionBehaviorGroup(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviorGroup::EntityCollisionBehaviorGroup(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs, {
	EntityGroundCollisionBehaviors::create(owner, attachedBehaviorArgs),
	EntityMovementCollisionBehaviors::create(owner, attachedBehaviorArgs),
	EntityWeaponCollisionBehaviors::create(owner, attachedBehaviorArgs),
	})
{
}

EntityCollisionBehaviorGroup::~EntityCollisionBehaviorGroup()
{
}

void EntityCollisionBehaviorGroup::onLoad()
{
}
