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

const float EntityMovementBehavior::MoveAcceleration = 5800.0f;
const Vec2 EntityMovementBehavior::SwimAcceleration = Vec2(8000.0f, 420.0f);
const float EntityMovementBehavior::JumpVelocity = 7680.0f;

EntityMovementBehavior* EntityMovementBehavior::create(GameObject* owner, std::string attachedBehaviorArgs)
{
	EntityMovementBehavior* instance = new EntityMovementBehavior(owner, attachedBehaviorArgs);

	instance->autorelease();

	return instance;
}

EntityMovementBehavior::EntityMovementBehavior(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityMovementBehavior::~EntityMovementBehavior()
{
	this->movement = Vec2::ZERO;
}

void EntityMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->entity == nullptr || this->entity->isCinimaticHijacked || this->entity->getIsPlatformerDisabled())
	{
		return;
	}

	EntityMovementCollisionBehavior* movementCollision = this->entity->getAttachedBehavior<EntityMovementCollisionBehavior>();
	EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();

	if (movementCollision == nullptr)
	{
		return;
	}

	if (this->entity->getStateOrDefaultBool(StateKeys::IsDead, false))
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
			// Move in the x direction unless hitting a wall while not standing on anything (this->entity prevents wall jumps)
			if ((this->movement.x < 0.0f && !movementCollision->hasLeftWallCollision()) ||
				(this->movement.x > 0.0f && !movementCollision->hasRightWallCollision()))
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

void EntityMovementBehavior::onLoad()
{
	this->scheduleUpdate();
}
