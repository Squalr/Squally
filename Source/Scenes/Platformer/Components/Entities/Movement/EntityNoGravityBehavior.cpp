#include "EntityNoGravityBehavior.h"

#include "base/CCEventCustom.h"
#include "base/CCEventListenerCustom.h"
#include "base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/Components/Entities/Collision/EntityCollisionBehaviorBase.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EntityNoGravityBehavior::MapKey = "no-gravity";

EntityNoGravityBehavior* EntityNoGravityBehavior::create(GameObject* owner)
{
	EntityNoGravityBehavior* instance = new EntityNoGravityBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityNoGravityBehavior::EntityNoGravityBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityNoGravityBehavior::~EntityNoGravityBehavior()
{
}

void EntityNoGravityBehavior::onLoad()
{
	this->entity->watchForComponent<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* behavior)
	{
		behavior->movementCollision->setGravityFlagEnabled(false);
	});
}

void EntityNoGravityBehavior::onDisable()
{
	super::onDisable();
}
