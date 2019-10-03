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

EntityCollisionBehavior* EntityCollisionBehavior::create(GameObject* owner)
{
	EntityCollisionBehavior* instance = new EntityCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityCollisionBehavior::EntityCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		CollisionType collisionType = CollisionType(PlatformerCollisionType::Enemy);

		if (dynamic_cast<Squally*>(this->entity) != nullptr)
		{
			collisionType = CollisionType(PlatformerCollisionType::Player);
		}
		else if (dynamic_cast<PlatformerFriendly*>(this->entity) != nullptr)
		{
			collisionType = CollisionType(PlatformerCollisionType::FriendlyNpc);
		}

		this->entityCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(this->entity->getEntitySize(), 0.9f, 8.0f),
			collisionType,
			false,
			false
		);

		Vec2 collisionOffset = this->entity->getCollisionOffset();

		if (this->entity->isFlippedY())
		{
			Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
			this->entityCollision->inverseGravity();
			this->entityCollision->getPhysicsBody()->setPositionOffset(offset);
		}
		else
		{
			Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getMovementSize().height / 2.0f);
			this->entityCollision->getPhysicsBody()->setPositionOffset(offset);
		}

		this->addChild(this->entityCollision);

		this->scheduleUpdate();
	}
}

EntityCollisionBehavior::~EntityCollisionBehavior()
{
}

void EntityCollisionBehavior::update(float dt)
{
	super::update(dt);
}

void EntityCollisionBehavior::onLoad()
{
}
