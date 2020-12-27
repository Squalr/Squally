#include "EntityMovementBehavior.h"

#include "cocos/base/CCValue.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/WorldSound.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityJumpCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementBehavior::MapKey = "entity-movement";
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
	this->jumpSound = nullptr;
	this->swimSounds = std::vector<WorldSound*>();
	this->walkSounds = std::vector<WorldSound*>();
	this->swimSoundIndex = 0;
	this->walkSoundIndex = 0;
	this->entityCollision = nullptr;
	this->groundCollision = nullptr;
	this->jumpBehavior = nullptr;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		this->jumpSound = WorldSound::create(this->entity->getJumpSound());

		for (auto next : this->entity->getSwimSounds())
		{
			WorldSound* swimSound = WorldSound::create(next);

			swimSound->setCustomMultiplier(0.25f);
			swimSound->enableZDepth();
			
			this->swimSounds.push_back(swimSound);

			this->addChild(swimSound);
		}

		for (auto next : this->entity->getWalkSounds())
		{
			WorldSound* walkSound = WorldSound::create(next);

			walkSound->setCustomMultiplier(0.25f);
			walkSound->enableZDepth();
			
			this->walkSounds.push_back(walkSound);

			this->addChild(walkSound);
		}

		this->addChild(this->jumpSound);
	}

	this->preCinematicPosition = Vec2::ZERO;
	this->prePatrolPosition = Vec2::ZERO;
}

EntityMovementBehavior::~EntityMovementBehavior()
{
}

void EntityMovementBehavior::onLoad()
{
	this->entity->listenForStateWrite(StateKeys::CinematicDestinationX, [=](Value value)
	{
		this->preCinematicPosition = this->entity->getPosition();
	});

	this->entity->listenForStateWrite(StateKeys::PatrolDestinationX, [=](Value value)
	{
		this->prePatrolPosition = this->entity->getPosition();
	});
	
	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollision)
	{
		this->entityCollision = entityCollision;
	});

	this->entity->watchForAttachedBehavior<EntityGroundCollisionBehavior>([=](EntityGroundCollisionBehavior* groundCollision)
	{
		this->groundCollision = groundCollision;
	});

	this->entity->watchForAttachedBehavior<EntityJumpCollisionBehavior>([=](EntityJumpCollisionBehavior* jumpBehavior)
	{
		this->jumpBehavior = jumpBehavior;
	});

	this->scheduleUpdate();
}

void EntityMovementBehavior::onDisable()
{
	super::onDisable();
}

void EntityMovementBehavior::update(float dt)
{
	super::update(dt);

	if (this->entityCollision == nullptr || this->groundCollision == nullptr || this->jumpBehavior == nullptr)
	{
		return;
	}

	Vec2 movement = Vec2(
		this->entity->getRuntimeStateOrDefaultFloat(StateKeys::MovementX, 0.0f),
		this->entity->getRuntimeStateOrDefaultFloat(StateKeys::MovementY, 0.0f)
	);

	if (!this->entity->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true))
	{
		movement = Vec2::ZERO;
	}
	else
	{
		bool isCinematicHijacked = this->entity->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false);
		bool isMountHijacked = this->entity->getRuntimeStateOrDefaultBool(StateKeys::MountHijacked, false);
		
		if (isCinematicHijacked || isMountHijacked)
		{
			movement = Vec2::ZERO;
		}

		this->applyPatrolMovement(&movement);
		this->applyCinematicMovement(&movement);
	}

	Vec2 velocity = this->entityCollision->getVelocity();

	bool canJump = this->jumpBehavior == nullptr ? false : this->jumpBehavior->canJump();
	PlatformerEntity::ControlState controlState = this->entity->getControlState();

	switch (controlState)
	{
		default:
		case PlatformerEntity::ControlState::Normal:
		{
			this->entityCollision->enableNormalPhysics();
			bool hasLeftCollision = this->entityCollision->hasLeftWallCollision();
			bool hasRightCollision = this->entityCollision->hasRightWallCollision();
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

				if (!this->jumpSound->isPlaying())
				{
					this->jumpSound->play();
				}

				this->entity->getAnimations()->playAnimation(this->entity->getJumpAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(0.85f));
			}

			if (std::abs(movement.y) < 0.15f)
			{
				if (std::abs(movement.x) > 0.15f)
				{
					this->entity->getAnimations()->playAnimation("Walk", SmartAnimationNode::AnimationPlayMode::Repeat, SmartAnimationNode::AnimParams(0.65f));

					if (this->groundCollision->isOnGround()
						&& !this->walkSounds.empty()
						&& !std::any_of(this->walkSounds.begin(), this->walkSounds.end(), [=](WorldSound* walkSound)
						{
							return walkSound->isPlaying();
						}))
					{
						this->walkSoundIndex = MathUtils::wrappingNormalize(this->walkSoundIndex + 1, 0, this->walkSounds.size() - 1);
						this->walkSounds[this->walkSoundIndex]->play();
					}
				}
				else
				{
					if (this->entity->getAnimations()->getCurrentAnimation() == "Walk")
					{
						this->entity->getAnimations()->clearAnimationPriority();
					}
					
					this->entity->getAnimations()->playAnimation("Idle", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, SmartAnimationNode::AnimParams(0.5f));
				}
			}

			break;
		}
		case PlatformerEntity::ControlState::Swimming:
		{
			this->entityCollision->enableWaterPhysics();

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
				if (!this->swimSounds.empty() && !std::any_of(this->swimSounds.begin(), this->swimSounds.end(), [=](WorldSound* swimSound)
					{
						return swimSound->isPlaying();
					}))
				{
					this->swimSoundIndex = MathUtils::wrappingNormalize(this->swimSoundIndex + 1, 0, this->swimSounds.size() - 1);
					this->swimSounds[this->swimSoundIndex]->play();
				}

				this->entity->getAnimations()->playAnimation(this->entity->getSwimAnimation(), SmartAnimationNode::AnimationPlayMode::Repeat,SmartAnimationNode::AnimParams(0.75f));
			}
			else if (this->entity->getAnimations()->getCurrentAnimation() == this->entity->getSwimAnimation())
			{
				this->entity->getAnimations()->clearAnimationPriority();
				this->entity->getAnimations()->playAnimation();
			}

			break;
		}
	}
	
	// Save velocity
	this->entityCollision->setVelocity(velocity);

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
	bool hasCinematicMovement = this->entity->hasRuntimeState(StateKeys::CinematicDestinationX);

	if (hasCinematicMovement)
	{
		float cinematicDestionationX = this->entity->getRuntimeStateOrDefaultFloat(StateKeys::CinematicDestinationX, 0.0f);
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

void EntityMovementBehavior::cancelWaterSfx()
{
	for (auto next : this->swimSounds)
	{
		next->stop();
	}
}

void EntityMovementBehavior::applyPatrolMovement(Vec2* movement)
{
	bool hasCinematicMovement = this->entity->hasRuntimeState(StateKeys::CinematicDestinationX);
	bool isCinematicHijacked = this->entity->getRuntimeStateOrDefaultBool(StateKeys::CinematicHijacked, false);
	bool hasPatrolMovement = this->entity->hasRuntimeState(StateKeys::PatrolDestinationX);

	if (!hasCinematicMovement && !isCinematicHijacked && hasPatrolMovement)
	{
		float patrolDestionationX = this->entity->getRuntimeStateOrDefaultFloat(StateKeys::PatrolDestinationX, 0.0f);
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
	bool hasCinematicMovement = this->entity->hasRuntimeState(StateKeys::CinematicDestinationX);
	
	if (hasCinematicMovement)
	{
		float cinematicDestionationX = this->entity->getRuntimeStateOrDefaultFloat(StateKeys::CinematicDestinationX, 0.0f);
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
	bool hasCinematicMovement = this->entity->hasRuntimeState(StateKeys::CinematicDestinationX);
	bool hasPatrolMovement = this->entity->hasRuntimeState(StateKeys::PatrolDestinationX);

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
		float patrolDestionationX = this->entity->getRuntimeStateOrDefaultFloat(StateKeys::PatrolDestinationX, 0.0f);
		bool patrolMovementDirectionLeft = patrolDestionationX < this->prePatrolPosition.x;
		Vec2 entityPosition = GameUtils::getWorldCoords(this->entity);

		if ((patrolMovementDirectionLeft && entityPosition.x <= patrolDestionationX) ||
			(!patrolMovementDirectionLeft && entityPosition.x >= patrolDestionationX))
		{
			this->entity->clearState(StateKeys::PatrolDestinationX);
			this->entity->setState(StateKeys::PatrolDestinationReached, Value(true));
		}
	}
}
