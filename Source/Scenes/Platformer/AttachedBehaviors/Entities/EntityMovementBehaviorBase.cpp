#include "EntityMovementBehaviorBase.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/PlatformerEntity.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

EntityMovementBehaviorBase::EntityMovementBehaviorBase(GameObject* owner, std::string attachedBehaviorArgs) : super(owner, attachedBehaviorArgs)
{
	this->entity = static_cast<PlatformerEntity*>(owner);
}

EntityMovementBehaviorBase::~EntityMovementBehaviorBase()
{
}

void EntityMovementBehaviorBase::update(float dt)
{
	super::update(dt);

	if (this->entity->isCinimaticHijacked)
	{
		return;
	}

	if (this->entity->isDead() && this->entity->movement != Vec2::ZERO)
	{
		this->entity->movement = Vec2::ZERO;
	}

	Vec2 velocity = this->entity->movementCollision->getVelocity();

	switch (this->entity->controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			// Move in the x direction unless hitting a wall while not standing on anything (this->entity prevents wall jumps)
			if ((this->entity->movement.x < 0.0f && this->entity->leftCollision->getCurrentCollisions().empty()) ||
				(this->entity->movement.x > 0.0f && this->entity->rightCollision->getCurrentCollisions().empty()))
			{
				velocity.x += this->entity->movement.x * PlatformerEntity::MoveAcceleration * dt;
			}

			if (this->entity->movement.y > 0.0f && this->entity->isOnGround())
			{
				velocity.y = this->entity->movement.y * PlatformerEntity::JumpVelocity;

				this->entity->performJumpAnimation();
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			const float minSpeed = PlatformerEntity::SwimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && this->entity->movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && this->entity->movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += this->entity->movement.x * PlatformerEntity::SwimAcceleration.x * dt;
			velocity.y += this->entity->movement.y * PlatformerEntity::SwimAcceleration.y * dt;

			if (this->entity->movement != Vec2::ZERO)
			{
				this->entity->performSwimAnimation();
			}

			break;
		}
	}
	
	// Apply velocity
	this->entity->movementCollision->setVelocity(velocity);

	// Update flip
	if (this->entity->animationNode != nullptr)
	{
		if (this->entity->movement.x < 0.0f)
		{
			this->entity->animationNode->setFlippedX(true);
		}
		else if (this->entity->movement.x > 0.0f)
		{
			this->entity->animationNode->setFlippedX(false);
		}
	}
}

void EntityMovementBehaviorBase::onLoad()
{
	this->scheduleUpdate();
}
