#include "EntityCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityWeaponCollisionBehavior.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviorGroup::MapKeyAttachedBehavior = "entity-collision-group";

EntityCollisionBehaviorGroup* EntityCollisionBehaviorGroup::create(GameObject* owner)
{
	EntityCollisionBehaviorGroup* instance = new EntityCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviorGroup::EntityCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityGroundCollisionBehavior::create(owner),
	EntityMovementCollisionBehavior::create(owner),
	EntityWeaponCollisionBehavior::create(owner),
	})
{
}

EntityCollisionBehaviorGroup::~EntityCollisionBehaviorGroup()
{
}

void EntityCollisionBehaviorGroup::onLoad()
{
}
