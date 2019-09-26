#include "EntityNoCollisionBehavior.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string EntityNoCollisionBehavior::MapKeyAttachedBehavior = "entity-no-collision";

EntityNoCollisionBehavior* EntityNoCollisionBehavior::create(GameObject* owner)
{
	EntityNoCollisionBehavior* instance = new EntityNoCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityNoCollisionBehavior::EntityNoCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityNoCollisionBehavior::~EntityNoCollisionBehavior()
{
}

void EntityNoCollisionBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityCollisionBehavior>([=](EntityCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->entityCollision->setPhysicsEnabled(false);
	});

	this->entity->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->movementCollision->setPhysicsEnabled(false);
	});
}
