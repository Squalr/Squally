#include "NpcCollisionBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/NpcBase.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string NpcCollisionBehaviors::MapKeyAttachedBehavior = "npc-collisions";

NpcCollisionBehaviors* NpcCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	NpcCollisionBehaviors* instance = new NpcCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

NpcCollisionBehaviors::NpcCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->npc = static_cast<NpcBase*>(owner);
}

NpcCollisionBehaviors::~NpcCollisionBehaviors()
{
}

void NpcCollisionBehaviors::onLoad()
{
	this->npc->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PlayerWeapon }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}
