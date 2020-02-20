#include "EntityMovementBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityJumpCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityMovementCollisionBehavior.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementBehavior::MapKeyAttachedBehavior = "entity-movement";
const float EntityMovementBehavior::DefaultWalkAcceleration = 4800.0f;
const float EntityMovementBehavior::DefaultRunAcceleration = 5600.0f;
const Vec2 EntityMovementBehavior::DefaultSwimAcceleration = Vec2(8000.0f, 420.0f);
const float EntityMovementBehavior::DefaultJumpVelocity = 7680.0f;

EntityMovementBehavior* EntityMovementBehavior::create(GameObject* owner)
{
	EntityMovementBehavior* instance = new EntityMovementBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMovementBehavior::EntityMovementBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->moveAcceleration = EntityMovementBehavior::DefaultRunAcceleration;
	this->swimAcceleration = EntityMovementBehavior::DefaultSwimAcceleration;
	this->jumpVelocity = EntityMovementBehavior::DefaultJumpVelocity;

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
	EntityJumpCollisionBehavior* jumpBehavior = this->entity->getAttachedBehavior<EntityJumpCollisionBehavior>();

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
		bool isCinematicHijacked = this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false);
		
		if (isCinematicHijacked)
		{
			movement = Vec2::ZERO;
		}

		this->applyPatrolMovement(&movement);
		this->applyCinematicMovement(&movement);
	}

	Vec2 velocity = movementCollision->getVelocity();

	bool canJump = jumpBehavior == nullptr ? false : jumpBehavior->canJump();
	PlatformerEntity::ControlState controlState = this->entity->getControlState();

	switch (controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			movementCollision->enableNormalPhysics();
			bool hasLeftCollision = movementCollision->hasLeftWallCollision();
			bool hasRightCollision = movementCollision->hasRightWallCollision();
			bool movingIntoLeftWall = (movement.x < 0.0f && hasLeftCollision);
			bool movingIntoRightWall = (movement.x > 0.0f && hasRightCollision);

			// Only apply movement velocity if not running into a wall. Prevents visual jitter.
			if ((!movingIntoLeftWall && !movingIntoRightWall) || (hasLeftCollision && hasRightCollision))
			{
				velocity.x += movement.x * this->moveAcceleration * dt;
			}

			if (movement.y > 0.0f && canJump)
			{
				velocity.y = movement.y * this->jumpVelocity;

				this->entity->getAnimations()->playAnimation(this->entity->getJumpAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 0.85f);
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			movementCollision->enableWaterPhysics();

			const float minSpeed = this->swimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += movement.x * this->swimAcceleration.x * dt;
			velocity.y += movement.y * this->swimAcceleration.y * dt;

			if (movement != Vec2::ZERO)
			{
				this->entity->getAnimations()->playAnimation(this->entity->getSwimAnimation(), SmartAnimationNode::AnimationPlayMode::Repeat, 0.75f);
			}

			break;
		}
	}

	if (std::abs(movement.y) < 0.15f)
	{
		if (std::abs(movement.x) > 0.15f)
		{
			this->entity->getAnimations()->playAnimation("Walk", SmartAnimationNode::AnimationPlayMode::Repeat, 0.65f);
		}
		else
		{
			if (this->entity->getAnimations()->getCurrentAnimation() == "Walk")
			{
				this->entity->getAnimations()->clearAnimationPriority();
			}
			
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

	this->checkPatrolMovementComplete();
	this->checkCinematicMovementComplete();
}

void EntityMovementBehavior::applyCinematicMovement(Vec2* movement)
{
	bool hasCinematicMovement = this->entity->hasState(StateKeys::CinematicDestinationX);

	if (hasCinematicMovement)
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

void EntityMovementBehavior::setMoveAcceleration(float moveAcceleration)
{
	this->moveAcceleration = moveAcceleration;
}

void EntityMovementBehavior::setSwimAcceleration(cocos2d::Vec2 swimAcceleration)
{
	this->swimAcceleration = swimAcceleration;
}

void EntityMovementBehavior::setJumpVelocity(float jumpVelocity)
{
	this->jumpVelocity = jumpVelocity;
}

void EntityMovementBehavior::applyPatrolMovement(Vec2* movement)
{
	bool hasCinematicMovement = this->entity->hasState(StateKeys::CinematicDestinationX);
	bool isCinematicHijacked = this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false);
	bool hasPatrolMovement = this->entity->hasState(StateKeys::PatrolDestinationX);

	if (!hasCinematicMovement && !isCinematicHijacked && hasPatrolMovement)
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
			this->entity->clearState(StateKeys::PatrolDestinationReached);
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
