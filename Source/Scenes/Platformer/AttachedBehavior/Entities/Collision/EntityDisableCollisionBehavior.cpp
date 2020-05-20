#include "EntityDisableCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityDisableCollisionBehavior::MapKey = "disable-collision";

EntityDisableCollisionBehavior* EntityDisableCollisionBehavior::create(GameObject* owner)
{
	EntityDisableCollisionBehavior* instance = new EntityDisableCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDisableCollisionBehavior::EntityDisableCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityDisableCollisionBehavior::~EntityDisableCollisionBehavior()
{
}

void EntityDisableCollisionBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* behavior)
	{
		behavior->movementCollision->setPhysicsEnabled(false);
		behavior->leftCollision->setPhysicsEnabled(false);
		behavior->rightCollision->setPhysicsEnabled(false);
	});
}

void EntityDisableCollisionBehavior::onDisable()
{
	super::onDisable();
}
