#include "EntityMovementCollisionBehaviors.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementCollisionBehaviors::MapKeyAttachedBehavior = "entity-movement-collisions";

EntityMovementCollisionBehaviors* EntityMovementCollisionBehaviors::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityMovementCollisionBehaviors* instance = new EntityMovementCollisionBehaviors(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityMovementCollisionBehaviors::EntityMovementCollisionBehaviors(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMovementCollisionBehaviors::~EntityMovementCollisionBehaviors()
{
}

void EntityMovementCollisionBehaviors::onLoad()
{
	CollisionType collisionType = CollisionType(PlatformerCollisionType::Movement);

	if (static_cast<Squally*>(this->entity) == nullptr)
	{
		collisionType = CollisionType(PlatformerCollisionType::PlayerMovement);
	}

	Size movementCollisionSize = Size(128.0f, 224.0f);

	this->movementCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(movementCollisionSize, this->entity->entityScale, 8.0f),
		collisionType,
		true,
		false
	);

	Size movementSize = movementCollisionSize * this->entity->entityScale;
	Vec2 scaledColOffset = this->entity->entityCollisionOffset * this->entity->entityScale;

	this->movementCollision->bindTo(this->entity);
	this->movementCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(0.0f, this->entity->entitySize.height / 2.0f));

	this->entity->entityCollision->getPhysicsBody()->setPositionOffset(scaledColOffset + Vec2(0.0f, movementSize.height / 2.0f));
	this->entity->clickHitbox->setPosition(Vec2(movementSize.width / 2.0f, movementSize.height / 2.0f));

	this->entity->addChild(this->movementCollision);

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		// No collision when not standing on anything, or if already on a different platform
		if (this->entity->getStateOrDefault(StateKeys::IsOnGround, Value(false)).asBool() || 
			collisionData.other->getStateOrDefault(StateKeys::CollisionObjectIsStandingOnOther, Value(false)).asBool() )
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->movementCollision->setGravityEnabled(false);
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;
		this->movementCollision->setVerticalDampening(PlatformerEntity::SwimVerticalDrag);

		// Clear current animation
		this->entity->animationNode->playAnimation("Idle");
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->movementCollision->setGravityEnabled(true);
		this->entity->controlState = PlatformerEntity::ControlState::Normal;
		this->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);

		// Animate jumping out of water
		if (this->movementCollision->getVelocity().y > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, PlatformerEntity::JumpVelocity));

			this->entity->animationNode->playAnimation("Jump");
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entity->setState(StateKeys::MovementCollisionObjectPtr, Value(this->movementCollision));
}

void EntityMovementCollisionBehaviors::update(float dt)
{
	super::update(dt);
}
