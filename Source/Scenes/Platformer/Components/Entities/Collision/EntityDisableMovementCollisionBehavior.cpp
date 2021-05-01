#include "EntityDisableMovementCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityDisableMovementCollisionBehavior::MapKey = "disable-movement-collision";

EntityDisableMovementCollisionBehavior* EntityDisableMovementCollisionBehavior::create(GameObject* owner)
{
	EntityDisableMovementCollisionBehavior* instance = new EntityDisableMovementCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityDisableMovementCollisionBehavior::EntityDisableMovementCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityDisableMovementCollisionBehavior::~EntityDisableMovementCollisionBehavior()
{
}

void EntityDisableMovementCollisionBehavior::onLoad()
{
	this->entity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* behavior)
	{
		behavior->movementCollision->setPhysicsEnabled(false);
		behavior->leftCollision->setPhysicsEnabled(false);
		behavior->rightCollision->setPhysicsEnabled(false);
	});
}

void EntityDisableMovementCollisionBehavior::onDisable()
{
	super::onDisable();
}
