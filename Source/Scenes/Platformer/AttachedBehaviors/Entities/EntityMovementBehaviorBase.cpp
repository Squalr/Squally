#include "EntityMovementBehaviorBase.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehaviors/Entities/Collision/EntityGroundCollisionBehaviors.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

EntityMovementBehaviorBase::EntityMovementBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMovementBehaviorBase::~EntityMovementBehaviorBase()
{
	this->movement = Vec2::ZERO;
}

void EntityMovementBehaviorBase::update(float dt)
{
	super::update(dt);

	CollisionObject* movementCollision = static_cast<CollisionObject*>(this->entity->getStateOrDefault(StateKeys::MovementCollisionObjectPtr, Value(nullptr)).asPointer());
	CollisionObject* leftCollision = static_cast<CollisionObject*>(this->entity->getStateOrDefault(StateKeys::LeftWallCollisionObjectPtr, Value(nullptr)).asPointer());
	CollisionObject* rightCollision = static_cast<CollisionObject*>(this->entity->getStateOrDefault(StateKeys::RightWallCollisionObjectPtr, Value(nullptr)).asPointer());
	
	if (movementCollision == nullptr || leftCollision == nullptr || rightCollision == nullptr || this->entity->isCinimaticHijacked)
	{
		return;
	}

	if (this->entity->isDead() && this->movement != Vec2::ZERO)
	{
		this->movement = Vec2::ZERO;
	}

	Vec2 velocity = movementCollision->getVelocity();

	EntityGroundCollisionBehaviors* groundBehaviors = this->entity->getAttachedBehavior<EntityGroundCollisionBehaviors>();

	bool isOnGround = groundBehaviors == nullptr ? false : groundBehaviors->isOnGround();

	switch (this->entity->controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			// Move in the x direction unless hitting a wall while not standing on anything (this->entity prevents wall jumps)
			if ((this->movement.x < 0.0f && leftCollision->getCurrentCollisions().empty()) ||
				(this->movement.x > 0.0f && rightCollision->getCurrentCollisions().empty()))
			{
				velocity.x += this->movement.x * PlatformerEntity::MoveAcceleration * dt;
			}

			if (this->movement.y > 0.0f && isOnGround)
			{
				velocity.y = this->movement.y * PlatformerEntity::JumpVelocity;

				this->entity->performJumpAnimation();
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			const float minSpeed = PlatformerEntity::SwimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && this->movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && this->movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += this->movement.x * PlatformerEntity::SwimAcceleration.x * dt;
			velocity.y += this->movement.y * PlatformerEntity::SwimAcceleration.y * dt;

			if (this->movement != Vec2::ZERO)
			{
				this->entity->performSwimAnimation();
			}

			break;
		}
	}
	
	// Save velocity
	movementCollision->setVelocity(velocity);

	this->entity->setState(StateKeys::VelocityX, Value(velocity.x));
	this->entity->setState(StateKeys::VelocityY, Value(velocity.y));

	// Update flip
	if (this->entity->animationNode != nullptr)
	{
		if (this->movement.x < 0.0f)
		{
			this->entity->animationNode->setFlippedX(true);
		}
		else if (this->movement.x > 0.0f)
		{
			this->entity->animationNode->setFlippedX(false);
		}
	}
}

void EntityMovementBehaviorBase::onLoad()
{
	this->scheduleUpdate();
}
