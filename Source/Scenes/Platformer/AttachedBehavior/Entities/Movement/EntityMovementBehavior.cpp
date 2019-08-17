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

	this->movement = Vec2::ZERO;
}

EntityMovementBehavior::~EntityMovementBehavior()
{
}

void EntityMovementBehavior::onLoad()
{
	this->scheduleUpdate();
}

void EntityMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->entity == nullptr || this->entity->getStateOrDefaultBool(StateKeys::CinematicHijacked, false))
	{
		return;
	}

	EntityMovementCollisionBehavior* movementCollision = this->entity->getAttachedBehavior<EntityMovementCollisionBehavior>();
	EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();

	if (movementCollision == nullptr)
	{
		return;
	}

	if (!this->entity->getStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		this->movement = Vec2::ZERO;
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
			bool movingIntoLeftWall = (this->movement.x < 0.0f && hasLeftCollision);
			bool movingIntoRightWall = (this->movement.x > 0.0f && hasRightCollision);

			// Move in the x direction unless hitting a wall while not standing on anything (this->entity prevents wall jumps)
			if ((!movingIntoLeftWall && !movingIntoRightWall) || (hasLeftCollision && hasRightCollision))
			{
				velocity.x += this->movement.x * EntityMovementBehavior::MoveAcceleration * dt;
			}

			if (this->movement.y > 0.0f && isOnGround)
			{
				velocity.y = this->movement.y * EntityMovementBehavior::JumpVelocity;

				this->entity->performJumpAnimation();
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			const float minSpeed = EntityMovementBehavior::SwimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && this->movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && this->movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += this->movement.x * EntityMovementBehavior::SwimAcceleration.x * dt;
			velocity.y += this->movement.y * EntityMovementBehavior::SwimAcceleration.y * dt;

			if (this->movement != Vec2::ZERO)
			{
				this->entity->performSwimAnimation();
			}

			break;
		}
	}
	
	// Save velocity
	movementCollision->setVelocity(velocity);

	this->entity->setState(StateKeys::VelocityX, Value(velocity.x), false);
	this->entity->setState(StateKeys::VelocityY, Value(velocity.y), false);

	// Update flip
	if (this->entity->getAnimations() != nullptr)
	{
		if (this->movement.x < 0.0f)
		{
			this->entity->getAnimations()->setFlippedX(true);
		}
		else if (this->movement.x > 0.0f)
		{
			this->entity->getAnimations()->setFlippedX(false);
		}
	}
}
