#include "EntityCollisionBehaviorGroup.h"

#include "Engine/Maps/GameObject.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHeadCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityHoverCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityJumpCollisionBehavior.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityWeaponCollisionBehavior.h"

using namespace cocos2d;

const std::string EntityCollisionBehaviorGroup::MapKey = "entity-collision-group";

EntityCollisionBehaviorGroup* EntityCollisionBehaviorGroup::create(GameObject* owner)
{
	EntityCollisionBehaviorGroup* instance = new EntityCollisionBehaviorGroup(owner);

	instance->autorelease();

	return instance;
}

EntityCollisionBehaviorGroup::EntityCollisionBehaviorGroup(GameObject* owner) : super(owner, {
	EntityGroundCollisionBehavior::create(owner),
	EntityHeadCollisionBehavior::create(owner),
	EntityJumpCollisionBehavior::create(owner),
	EntityHoverCollisionBehavior::create(owner),
	})
{
}

EntityCollisionBehaviorGroup::~EntityCollisionBehaviorGroup()
{
}

void EntityCollisionBehaviorGroup::onLoad()
{
}
