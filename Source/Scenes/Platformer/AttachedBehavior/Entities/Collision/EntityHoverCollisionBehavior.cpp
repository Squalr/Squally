#include "EntityHoverCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityJumpCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityHoverCollisionBehavior::MapKey = "entity-movement-collisions";

EntityHoverCollisionBehavior* EntityHoverCollisionBehavior::create(GameObject* owner)
{
	EntityHoverCollisionBehavior* instance = new EntityHoverCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityHoverCollisionBehavior::EntityHoverCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->hoverCollision = nullptr;
	this->entityCollision = nullptr;
	this->groundCollision = nullptr;
	this->jumpCollision = nullptr;
	this->hoverAntiGravityCollisionDetector = nullptr;
	this->hoverAntiGravityTopCollisionDetector = nullptr;
	this->crouchProgress = 0.0f;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
}

EntityHoverCollisionBehavior::~EntityHoverCollisionBehavior()
{
	if (this->hoverCollision != nullptr && this->hoverCollision->getParent() != nullptr && this->hoverCollision->getParent() != this)
	{
		this->hoverCollision->getParent()->removeChild(this->hoverCollision);
	}
}

void EntityHoverCollisionBehavior::onLoad()
{
	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollision)
	{
		this->entityCollision = entityCollision;
	});

	this->entity->watchForAttachedBehavior<EntityGroundCollisionBehavior>([=](EntityGroundCollisionBehavior* groundCollision)
	{
		this->groundCollision = groundCollision;
	});

	this->entity->watchForAttachedBehavior<EntityJumpCollisionBehavior>([=](EntityJumpCollisionBehavior* jumpCollision)
	{
		this->jumpCollision = jumpCollision;
	});
	
	this->defer([=]()
	{
		this->buildHoverAntiGravityCollision();
		this->buildHoverCollision();
		this->toggleQueryable(true);
	});

	this->scheduleUpdate();
}

void EntityHoverCollisionBehavior::onDisable()
{
	super::onDisable();
	
	if (this->hoverCollision != nullptr)
	{
		this->hoverCollision->setPhysicsEnabled(false);
	}
}

void EntityHoverCollisionBehavior::update(float dt)
{
	super::update(dt);

	if (this->entity->getRuntimeStateOrDefaultFloat(StateKeys::MovementY, 0.0f) < 0.0f)
	{
		this->crouch(dt);
	}
	else
	{
		this->uncrouch(dt);
	}
	
	if (this->hoverAntiGravityCollisionDetector != nullptr
		&& this->hoverAntiGravityTopCollisionDetector != nullptr
		&& this->entityCollision != nullptr
		&& this->entityCollision->movementCollision != nullptr)
	{
		// Update anti-gravity to avoid jitter
		if (this->hoverAntiGravityCollisionDetector->hasCollisions() && !this->hoverAntiGravityTopCollisionDetector->hasCollisions())
		{
			this->entityCollision->movementCollision->setGravityDisabledOverride(true);

			if (this->entityCollision->movementCollision->getVelocity().y < 0.0f)
			{
				this->entityCollision->movementCollision->setVelocityY(0.0f);
			}
		}
		else
		{
			this->entityCollision->movementCollision->setGravityDisabledOverride(false);
		}
	}
}

void EntityHoverCollisionBehavior::crouch(float dt)
{
	static const float TimeToCrouch = 0.5f;

	if (this->crouchProgress >= 1.0f)
	{
		return;
	}

	this->crouchProgress = MathUtils::clamp(this->crouchProgress + dt * (1.0f / TimeToCrouch), 0.0f, 1.0f);

	this->rebuildHoverCrouchCollision();
}

void EntityHoverCollisionBehavior::uncrouch(float dt)
{
	static const float TimeToUncrouch = 0.5f;

	if (this->crouchProgress <= 0.0f)
	{
		return;
	}

	this->crouchProgress = MathUtils::clamp(this->crouchProgress - dt * (1.0f / TimeToUncrouch), 0.0f, 1.0f);

	this->rebuildHoverCrouchCollision();
}

void EntityHoverCollisionBehavior::rebuildHoverCrouchCollision()
{
	static const float MinCrouch = 0.75f;
	static const float MaxCrouch = 1.0f;

	float inverseProgress = MathUtils::clamp(1.0f - this->crouchProgress, 0.0f, 1.0f);
	Size hoverSize = this->getHoverSize(inverseProgress);

	this->hoverCollision->setPoints(CollisionObject::createBox(hoverSize));
	this->positionHoverCollision(inverseProgress);
}

Size EntityHoverCollisionBehavior::getHoverSize(float progress)
{
	static const float CrouchLowPoint = this->entity->getHoverHeight() / 2.5f;
	static const float UpwardsPadding = this->entity->getEntitySize().height;
	static const float MinCrouch = this->entity->getCollisionOffset().y + this->entity->getEntitySize().height + CrouchLowPoint;
	static const float MaxCrouch = this->entity->getCollisionOffset().y + this->entity->getHoverHeight() + UpwardsPadding;

	float crouchHeight = MinCrouch + (MaxCrouch - MinCrouch) * progress;

	return Size(
		std::max(this->entity->getEntitySize().width - 24.0f, 16.0f),
		crouchHeight
	);
}

void EntityHoverCollisionBehavior::positionHoverCollision(float progress)
{
	static const float CrouchLowPoint = this->entity->getHoverHeight() / 2.5f;
	static const float UpwardsPadding = this->entity->getEntitySize().height;
	static const float MinCrouchGround = this->entity->getCollisionOffset().y - CrouchLowPoint + EntityGroundCollisionBehavior::GroundCollisionOffset - EntityGroundCollisionBehavior::GroundCollisionHeight / 2.0f;
	static const float MaxCrouchGround = this->entity->getCollisionOffset().y - this->entity->getHoverHeight() + EntityGroundCollisionBehavior::GroundCollisionOffset- EntityGroundCollisionBehavior::GroundCollisionHeight / 2.0f;
	static const float MinCrouchJump = this->entity->getCollisionOffset().y - CrouchLowPoint + EntityJumpCollisionBehavior::JumpCollisionOffset - EntityJumpCollisionBehavior::JumpCollisionHeight / 2.0f;
	static const float MaxCrouchJump = this->entity->getCollisionOffset().y - this->entity->getHoverHeight() + EntityJumpCollisionBehavior::JumpCollisionOffset - EntityJumpCollisionBehavior::JumpCollisionHeight / 2.0f;

	static const Vec2 CollisionOffset = this->entity->getCollisionOffset();
	static const float OriginalHoverHeight = this->entity->getHoverHeight();
	static const Vec2 Offset = CollisionOffset + Vec2(0.0f, -OriginalHoverHeight / 2.0f);

	Size hoverSize = this->getHoverSize(progress);
	float hoverDelta = OriginalHoverHeight - hoverSize.height;

	this->hoverCollision->setPosition(Offset + Vec2(0.0f, hoverDelta / 2.0f + UpwardsPadding));

	// Reposition ground/jump collision to the bottom of the hover
	float crouchAdjustGroundY = MinCrouchGround + (MaxCrouchGround - MinCrouchGround) * progress;
	float crouchAdjustJumpY = MinCrouchJump + (MaxCrouchJump - MinCrouchJump) * progress;

	if (this->groundCollision != nullptr && this->groundCollision->getGroundCollision() != nullptr)
	{
		this->groundCollision->getGroundCollision()->setPosition(Vec2(this->entity->getCollisionOffset().x,  crouchAdjustGroundY));
	}

	if (this->jumpCollision != nullptr && this->jumpCollision->getJumpCollision() != nullptr)
	{
		this->jumpCollision->getJumpCollision()->setPosition(Vec2(this->entity->getCollisionOffset().x,  crouchAdjustJumpY));
	}
}

void EntityHoverCollisionBehavior::buildHoverCollision()
{
	if (this->hoverCollision != nullptr || this->entity->getHoverHeight() <= 0.0f)
	{
		return;
	}

	Size hoverSize = this->getHoverSize();
	CollisionType collisionType = CollisionType(PlatformerCollisionType::Hover);

	this->hoverCollision = CollisionObject::create(
		CollisionObject::createBox(hoverSize),
		// CollisionObject::createCapsulePolygon(hoverSize, 8.0f),
		collisionType,
		CollisionObject::Properties(true, false),
		Color4F::BLUE
	);
	
	this->hoverCollision->setName("entity movement");
	this->hoverCollision->bindTo(this->entity);
	this->hoverCollision->setGravityEnabled(false);
	this->positionHoverCollision();

	this->addChild(this->hoverCollision);
	
	this->hoverCollision->whileCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::SolidPlayerOnly }, [=](CollisionObject::CollisionData collisionData)
	{
		static const Vec2 HoverSpeed = Vec2(0.0f, 192.0f);
		static const float MinSpeed = 0.0f;

		if (this->groundCollision == nullptr
			|| this->entityCollision == nullptr
			|| this->entityCollision->movementCollision == nullptr
			|| this->groundCollision->getGroundCollision() == nullptr
			|| this->entity->controlState == PlatformerEntity::ControlState::Swimming)
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		if (this->entityCollision != nullptr)
		{
			Vec2 velocity = entityCollision->movementCollision->getVelocity();
			Vec2 gravity = entityCollision->movementCollision->getGravity();

			velocity.y = velocity.y <= MinSpeed ? MinSpeed : velocity.y;

			// Apply hover speed and counter-act gravity
			entityCollision->movementCollision->setVelocity(velocity + (HoverSpeed - gravity) * collisionData.dt);
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityHoverCollisionBehavior::buildHoverAntiGravityCollision()
{
	static const float AntiGravityDetectorSize = 32.0f;

	if (this->hoverAntiGravityCollisionDetector != nullptr || this->hoverAntiGravityTopCollisionDetector != nullptr || this->entity->getHoverHeight() <= 0.0f)
	{
		return;
	}

	float detectorWidth = std::max((this->entity->getEntitySize()).width + EntityGroundCollisionBehavior::GroundCollisionPadding * 2.0f, 8.0f);

	this->hoverAntiGravityCollisionDetector = CollisionObject::create(
		CollisionObject::createBox(
			Size(detectorWidth, AntiGravityDetectorSize)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::PURPLE
	);

	this->hoverAntiGravityTopCollisionDetector = CollisionObject::create(
		CollisionObject::createBox(
			Size(detectorWidth, AntiGravityDetectorSize)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GREEN
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, -this->entity->getEntitySize().height / 2.0f - this->entity->getHoverHeight() / 2.0f - AntiGravityDetectorSize / 2.0f);

	this->hoverAntiGravityCollisionDetector->setPosition(offset);
	this->hoverAntiGravityTopCollisionDetector->setPosition(offset + Vec2(0.0f, AntiGravityDetectorSize));

	this->addChild(this->hoverAntiGravityCollisionDetector);
	this->addChild(this->hoverAntiGravityTopCollisionDetector);

	this->hoverAntiGravityTopCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->hoverAntiGravityCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// See update(float dt) for anti-gravity logic

		return CollisionObject::CollisionResult::DoNothing;
	});
}
