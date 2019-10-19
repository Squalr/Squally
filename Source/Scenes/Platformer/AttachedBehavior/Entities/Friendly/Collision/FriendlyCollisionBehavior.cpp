#include "FriendlyCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerFriendly.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string FriendlyCollisionBehavior::MapKeyAttachedBehavior = "friendly-collisions";

FriendlyCollisionBehavior* FriendlyCollisionBehavior::create(GameObject* owner)
{
	FriendlyCollisionBehavior* instance = new FriendlyCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

FriendlyCollisionBehavior::FriendlyCollisionBehavior(GameObject* owner) : super(owner)
{
	this->npc = dynamic_cast<PlatformerFriendly*>(owner);

	if (this->npc == nullptr)
	{
		this->invalidate();
	}
}

FriendlyCollisionBehavior::~FriendlyCollisionBehavior()
{
}

void FriendlyCollisionBehavior::onLoad()
{
	this->npc->watchForAttachedBehavior<EntityMovementCollisionBehavior>([=](EntityMovementCollisionBehavior* collisionBehavior)
	{
		collisionBehavior->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
		{	
			return CollisionObject::CollisionResult::CollideWithPhysics;
		});
	});
}
