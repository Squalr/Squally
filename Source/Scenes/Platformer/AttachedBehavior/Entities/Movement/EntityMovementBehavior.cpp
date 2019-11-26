#include "EntityMovementBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementBehavior::MapKeyAttachedBehavior = "entity-movement";
const float EntityMovementBehavior::MoveAcceleration = 5800.0f;
const Vec2 EntityMovementBehavior::SwimAcceleration = Vec2(8000.0f, 420.0f);
const float EntityMovementBehavior::JumpVelocity = 7680.0f;

EntityMovementBehavior* EntityMovementBehavior::create(GameObject* owner)
{
	EntityMovementBehavior* instance = new EntityMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMovementBehavior::EntityMovementBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}

	this->preCinematicPosition = Vec2::ZERO;
	this->prePatrolPosition = Vec2::ZERO;
}

EntityMovementBehavior::~EntityMovementBehavior()
{
}

void EntityMovementBehavior::onLoad()
{
	this->scheduleUpdate();

	this->entity->listenForStateWrite(StateKeys::CinematicDestinationX, [=](Value value)
	{
		this->preCinematicPosition = this->entity->getPosition();
	});

	this->entity->listenForStateWrite(StateKeys::PatrolDestinationX, [=](Value value)
	{
		this->prePatrolPosition = this->entity->getPosition();
	});
}

void EntityMovementBehavior::update(float dt)
{
	super::update(dt);

	EntityMovementCollisionBehavior* movementCollision = this->entity->getAttachedBehavior<EntityMovementCollisionBehavior>();
	EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();

	if (movementCollision == nullptr)
	{
		return;
	}

	Vec2 movement = Vec2(
		this->entity->getStateOrDefaultFloat(StateKeys::MovementX, 0.0f),
		this->entity->getStateOrDefaultFloat(StateKeys::MovementY, 0.0f)
	);

	if (!this->entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		movement = Vec2::ZERO;
	}
	else
	{
		// this->applyPatrolMovement(&movement);
		this->applyCinematicMovement(&movement);
	}

	Vec2 velocity = movementCollision->getVelocity();

	bool isOnGround = groundBehavior == nullptr ? false : groundBehavior->isOnGround();

	switch (this->entity->controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			bool hasLeftCollision = movementCollision->hasLeftWallCollision();
			bool hasRightCollision = movementCollision->hasRightWallCollision();
			bool movingIntoLeftWall = (movement.x < 0.0f && hasLeftCollision);
			bool movingIntoRightWall = (movement.x > 0.0f && hasRightCollision);

			// Move in the x direction unless hitting a wall while not standing on anything (this->entity prevents wall jumps)
			if ((!movingIntoLeftWall && !movingIntoRightWall) || (hasLeftCollision && hasRightCollision))
			{
				velocity.x += movement.x * EntityMovementBehavior::MoveAcceleration * dt;
			}

			if (movement.y > 0.0f && isOnGround)
			{
				velocity.y = movement.y * EntityMovementBehavior::JumpVelocity;

				this->entity->performJumpAnimation();
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			const float minSpeed = EntityMovementBehavior::SwimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += movement.x * EntityMovementBehavior::SwimAcceleration.x * dt;
			velocity.y += movement.y * EntityMovementBehavior::SwimAcceleration.y * dt;

			if (movement != Vec2::ZERO)
			{
				this->entity->performSwimAnimation();
			}

			break;
		}
	}

	if (std::abs(movement.y) < 0.15f)
	{
		if (std::abs(movement.x) > 0.15f)
		{
			this->entity->getAnimations()->playAnimation("Walk", SmartAnimationNode::AnimationPlayMode::Repeat, 0.5f);
		}
		else
		{
			this->entity->getAnimations()->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 0.5f);
		}
	}
	
	// Save velocity
	movementCollision->setVelocity(velocity);

	this->entity->setState(StateKeys::VelocityX, Value(velocity.x), false);
	this->entity->setState(StateKeys::VelocityY, Value(velocity.y), false);

	// Update flip
	if (this->entity->getAnimations() != nullptr)
	{
		if (movement.x < 0.0f)
		{
			this->entity->getAnimations()->setFlippedX(true);
		}
		else if (movement.x > 0.0f)
		{
			this->entity->getAnimations()->setFlippedX(false);
		}
	}

	// this->checkPatrolMovementComplete();
	this->checkCinematicMovementComplete();
}

void EntityMovementBehavior::applyCinematicMovement(Vec2* movement)
{
	bool isCinematicHijacked = this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false);
	bool hasCinematicMovement = this->entity->hasState(StateKeys::CinematicDestinationX);

	if (isCinematicHijacked && hasCinematicMovement)
	{
		float cinematicDestionationX = this->entity->getStateOrDefaultFloat(StateKeys::CinematicDestinationX, 0.0f);
		bool cinematicMovementDirectionLeft = cinematicDestionationX < this->preCinematicPosition.x;

		if (cinematicMovementDirectionLeft)
		{
			movement->x = -1.0f;
		}
		else
		{
			movement->x = 1.0f;
		}
	}
}

void EntityMovementBehavior::applyPatrolMovement(Vec2* movement)
{
	bool isCinematicHijacked = this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false);
	bool hasPatrolMovement = this->entity->hasState(StateKeys::PatrolDestinationX);

	if (!isCinematicHijacked && hasPatrolMovement)
	{
		float patrolDestionationX = this->entity->getStateOrDefaultFloat(StateKeys::PatrolDestinationX, 0.0f);
		bool patrolMovementDirectionLeft = patrolDestionationX < this->prePatrolPosition.x;

		if (patrolMovementDirectionLeft)
		{
			movement->x = -1.0f;
		}
		else
		{
			movement->x = 1.0f;
		}
	}
}

void EntityMovementBehavior::checkCinematicMovementComplete()
{
	bool hasCinematicMovement = this->entity->hasState(StateKeys::CinematicDestinationX);
	
	if (hasCinematicMovement)
	{
		float cinematicDestionationX = this->entity->getStateOrDefaultFloat(StateKeys::CinematicDestinationX, 0.0f);
		bool cinematicMovementDirectionLeft = cinematicDestionationX < this->preCinematicPosition.x;

		if ((cinematicMovementDirectionLeft && this->entity->getPositionX() <= cinematicDestionationX) ||
			(!cinematicMovementDirectionLeft && this->entity->getPositionX() >= cinematicDestionationX))
		{
			this->entity->clearState(StateKeys::CinematicDestinationX);
			this->entity->setState(StateKeys::CinematicDestinationReached, Value(true));
		}
	}
}

void EntityMovementBehavior::checkPatrolMovementComplete()
{
	bool hasCinematicMovement = this->entity->hasState(StateKeys::CinematicDestinationX);
	bool hasPatrolMovement = this->entity->hasState(StateKeys::PatrolDestinationX);

	// Exit if doing cinematic movement. That has priority.
	if (hasCinematicMovement)
	{
		// Just clear any existing patrol state
		if (hasPatrolMovement)
		{
			this->entity->clearState(StateKeys::PatrolDestinationX);
			this->entity->setState(StateKeys::PatrolDestinationReached, Value(true));
		}

		return;
	}
	
	if (hasPatrolMovement)
	{
		float patrolDestionationX = this->entity->getStateOrDefaultFloat(StateKeys::PatrolDestinationX, 0.0f);
		bool patrolMovementDirectionLeft = patrolDestionationX < this->prePatrolPosition.x;

		if ((patrolMovementDirectionLeft && this->entity->getPositionX() <= patrolDestionationX) ||
			(!patrolMovementDirectionLeft && this->entity->getPositionX() >= patrolDestionationX))
		{
			this->entity->clearState(StateKeys::PatrolDestinationX);
			this->entity->setState(StateKeys::PatrolDestinationReached, Value(true));
		}
	}
}
