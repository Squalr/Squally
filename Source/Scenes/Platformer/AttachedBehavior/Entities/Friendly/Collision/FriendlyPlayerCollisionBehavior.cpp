#include "FriendlyPlayerCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string FriendlyPlayerCollisionBehavior::MapKey = "friendly-collisions";

FriendlyPlayerCollisionBehavior* FriendlyPlayerCollisionBehavior::create(GameObject* owner)
{
	FriendlyPlayerCollisionBehavior* instance = new FriendlyPlayerCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyPlayerCollisionBehavior::FriendlyPlayerCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

FriendlyPlayerCollisionBehavior::~FriendlyPlayerCollisionBehavior()
{
}

void FriendlyPlayerCollisionBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* collisionBehavior)
	{
		if (collisionBehavior->movementCollision != nullptr)
		{
			collisionBehavior->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
			{	
				return CollisionObject::CollisionResult::CollideWithPhysics;
			});
		}
	});
}

void FriendlyPlayerCollisionBehavior::onDisable()
{
	super::onDisable();
}
