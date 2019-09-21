#include "EntityMovementCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementCollisionBehavior::MapKeyAttachedBehavior = "entity-movement-collisions";
const float EntityMovementCollisionBehavior::WaterJumpVelocity = 7680.0f;
const float EntityMovementCollisionBehavior::SwimVerticalDrag = 0.93f;

EntityMovementCollisionBehavior* EntityMovementCollisionBehavior::create(GameObject* owner)
{
	EntityMovementCollisionBehavior* instance = new EntityMovementCollisionBehavior(owner);

	instance->autorelease();

	return instance;
}

EntityMovementCollisionBehavior::EntityMovementCollisionBehavior(GameObject* owner) : super(owner)
{
	this->entity = dynamic_cast<PlatformerEntity*>(owner);
	this->movementCollision = nullptr;
	this->leftCollision = nullptr;
	this->rightCollision = nullptr;
	this->movementCollisionBound = false;

	if (this->entity == nullptr)
	{
		this->invalidate();
	}
	else
	{
		CollisionType collisionType = CollisionType(PlatformerCollisionType::Movement);

		if (dynamic_cast<Squally*>(this->entity) != nullptr)
		{
			collisionType = CollisionType(PlatformerCollisionType::PlayerMovement);
		}

		this->movementCollision = CollisionObject::create(
			CollisionObject::createCapsulePolygon(this->entity->getMovementSize(), 1.0f, 8.0f),
			collisionType,
			true,
			false
		);

		this->movementCollision->getPhysicsBody()->setPositionOffset(this->entity->getCollisionOffset() + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f));
		
		this->addChild(this->movementCollision);
	}
}

EntityMovementCollisionBehavior::~EntityMovementCollisionBehavior()
{
}

void EntityMovementCollisionBehavior::onLoad()
{
	this->buildMovementCollision();
	this->buildWallDetectors();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocationPrefix + std::to_string((unsigned long long)(this->entity)), [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpArgs* args = static_cast<PlatformerEvents::WarpArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && this->movementCollision != nullptr)
		{
			this->movementCollision->setPosition(args->position);
			GameCamera::getInstance()->setCameraPositionToTrackedTarget();
		}
	}));
}

void EntityMovementCollisionBehavior::update(float dt)
{
	super::update(dt);

	if (!this->movementCollisionBound)
	{
		this->movementCollisionBound = true;
		this->movementCollision->bindTo(this->entity);
	}
}

Vec2 EntityMovementCollisionBehavior::getVelocity()
{
	return this->movementCollision->getVelocity();
}

void EntityMovementCollisionBehavior::setVelocity(Vec2 velocity)
{
	this->movementCollision->setVelocity(velocity);
}

bool EntityMovementCollisionBehavior::hasLeftWallCollision()
{
	return !this->leftCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehavior::hasRightWallCollision()
{
	return !this->rightCollision->getCurrentCollisions().empty();
}

void EntityMovementCollisionBehavior::buildMovementCollision()
{
	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();

		if (groundBehavior == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		// No collision when not standing on anything, or if already on a different platform
		if (!groundBehavior->isOnGround() || groundBehavior->isStandingOnSomethingOtherThan(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->movementCollision->setGravityEnabled(false);
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;
		this->movementCollision->setVerticalDampening(EntityMovementCollisionBehavior::SwimVerticalDrag);

		// Clear current animation
		this->entity->getAnimations()->playAnimation();
		
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
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, EntityMovementCollisionBehavior::WaterJumpVelocity));

			this->entity->getAnimations()->playAnimation("Jump", SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 0.85f);
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityMovementCollisionBehavior::buildWallDetectors()
{
	const Size wallDetectorSize = Size(std::max(this->entity->getEntitySize().width / 2.0f - 8.0f, 16.0f), std::max(this->entity->getEntitySize().height - 32.0f, 16.0f));

	this->leftCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 1.0f, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);
	this->rightCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 1.0f, 8.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);

	this->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Size entitySize = this->entity->getEntitySize();

	this->leftCollision->getPhysicsBody()->setPositionOffset(collisionOffset + Vec2(-entitySize.width / 2.0f + wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f));
	this->rightCollision->getPhysicsBody()->setPositionOffset(collisionOffset + Vec2(entitySize.width / 2.0f - wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f));

	this->addChild(this->leftCollision);
	this->addChild(this->rightCollision);
}
