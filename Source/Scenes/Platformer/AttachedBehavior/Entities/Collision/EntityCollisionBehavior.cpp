#include "EntityCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityCollisionBehavior::MapKeyAttachedBehavior = "entity-collisions";

EntityCollisionBehavior* EntityCollisionBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityCollisionBehavior* instance = new EntityCollisionBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityCollisionBehavior::EntityCollisionBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityCollisionBehavior::~EntityCollisionBehavior()
{
}

void EntityCollisionBehavior::onLoad()
{
	CollisionType collisionType = CollisionType(PlatformerCollisionType::Enemy);

	if (static_cast<Squally*>(this->entity) != nullptr)
	{
		collisionType = CollisionType(PlatformerCollisionType::Player);
	}
	else if (static_cast<PlatformerFriendly*>(this->entity) != nullptr)
	{
		collisionType = CollisionType(PlatformerCollisionType::FriendlyNpc);
	}

	this->entityCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(this->entity->getEntitySize(), 0.9f, 8.0f),
		collisionType,
		false,
		false
	);

	this->entityCollision->getPhysicsBody()->setPositionOffset(this->entity->entityCollisionOffset + Vec2(0.0f, this->entity->movementSize.height / 2.0f));

	this->addChild(this->entityCollision);
}
