#include "EntityMovementCollisionBehavior.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Physics/EngineCollisionTypes.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityHeadCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const std::string EntityMovementCollisionBehavior::MapKeyAttachedBehavior = "entity-movement-collisions";
const float EntityMovementCollisionBehavior::WaterJumpVelocity = 7680.0f;
const float EntityMovementCollisionBehavior::SwimVerticalDrag = 0.93f;
const float EntityMovementCollisionBehavior::StaticFriction = 256.0f;

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
			CollisionObject::createCapsulePolygon(this->entity->getMovementSize(), 1.0f, 8.0f, 0.0f),
			collisionType,
			true,
			false
		);

		Vec2 collisionOffset = this->entity->getCollisionOffset();

		if (this->entity->isFlippedY())
		{
			Vec2 offset = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->movementCollision->inverseGravity();
			this->movementCollision->getPhysicsBody()->setPositionOffset(offset);
		}
		else
		{
			Vec2 offset = collisionOffset + Vec2(0.0f, this->entity->getEntitySize().height / 2.0f);
			this->movementCollision->getPhysicsBody()->setPositionOffset(offset);
		}

		this->addChild(this->movementCollision);
	}
}

EntityMovementCollisionBehavior::~EntityMovementCollisionBehavior()
{
	if (this->movementCollision->getParent() != nullptr && this->movementCollision->getParent() != this)
	{
		this->movementCollision->getParent()->removeChild(this->movementCollision);
	}
}

void EntityMovementCollisionBehavior::onLoad()
{
	this->buildMovementCollision();
	this->buildWallDetectors();
	
	const std::string identifier = std::to_string((unsigned long long)(this->entity));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocationPrefix + identifier, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpArgs* args = static_cast<PlatformerEvents::WarpArgs*>(eventCustom->getUserData());
		
		if (args != nullptr && this->movementCollision != nullptr)
		{
			this->tryBind();
			this->movementCollision->setPosition(args->position);

			if (GameCamera::getInstance()->getCurrentTrackingData()->target == this->entity)
			{
				GameCamera::getInstance()->setCameraPositionToTrackedTarget();
			}
		}
	}));

	this->entity->listenForStateWrite(StateKeys::MovementX, [=](Value value)
	{
		float movementX = value.asFloat();

		if (movementX != 0.0f)
		{
			this->movementCollision->getPhysicsBody()->getFirstShape()->setFriction(0.0f);
		}
		else
		{
			this->movementCollision->getPhysicsBody()->getFirstShape()->setFriction(EntityMovementCollisionBehavior::StaticFriction);
		}
	});
}

void EntityMovementCollisionBehavior::update(float dt)
{
	super::update(dt);

	this->tryBind();
}

void EntityMovementCollisionBehavior::enableNormalPhysics()
{
	this->movementCollision->setGravityEnabled(true);
	this->movementCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);
}

void EntityMovementCollisionBehavior::enableWaterPhysics()
{
	this->movementCollision->setGravityEnabled(false);
	this->movementCollision->setVerticalDampening(EntityMovementCollisionBehavior::SwimVerticalDrag);
}

Vec2 EntityMovementCollisionBehavior::getVelocity()
{
	return this->movementCollision == nullptr ? Vec2::ZERO : this->movementCollision->getVelocity();
}

void EntityMovementCollisionBehavior::setVelocity(Vec2 velocity)
{
	if (this->movementCollision == nullptr)
	{
		return;
	}

	this->movementCollision->setVelocity(velocity);
}

bool EntityMovementCollisionBehavior::hasLeftWallCollision()
{
	return this->leftCollision == nullptr ? false : !this->leftCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehavior::hasRightWallCollision()
{
	return this->rightCollision == nullptr ? false : !this->rightCollision->getCurrentCollisions().empty();
}

bool EntityMovementCollisionBehavior::hasLeftWallCollisionWith(CollisionObject* collisonObject)
{
	for (auto next : this->leftCollision->getCurrentCollisions())
	{
		if (next == collisonObject)
		{
			return true;
		}
	}

	return false;
}

bool EntityMovementCollisionBehavior::hasRightWallCollisionWith(CollisionObject* collisonObject)
{
	for (auto next : this->rightCollision->getCurrentCollisions())
	{
		if (next == collisonObject)
		{
			return true;
		}
	}

	return false;
}

void EntityMovementCollisionBehavior::buildMovementCollision()
{
	if (this->movementCollision == nullptr)
	{
		return;
	}

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
	
	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{
		EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();
		EntityHeadCollisionBehavior* headBehavior = this->entity->getAttachedBehavior<EntityHeadCollisionBehavior>();

		if (groundBehavior == nullptr || headBehavior == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		if (groundBehavior->isStandingOn(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		if (headBehavior->hasHeadCollisionWith(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		EntityGroundCollisionBehavior* groundBehavior = this->entity->getAttachedBehavior<EntityGroundCollisionBehavior>();
		EntityHeadCollisionBehavior* headBehavior = this->entity->getAttachedBehavior<EntityHeadCollisionBehavior>();

		if (groundBehavior == nullptr || headBehavior == nullptr)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		if (groundBehavior->isStandingOn(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		// This is how we allow platforms to overlap -- the oldest-touched platform tends to be the correct collision target
		if (groundBehavior->isStandingOnSomethingOtherThan(collisionData.other))
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		if (!headBehavior->hasHeadCollisionWith(collisionData.other))
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}

		// No collision when not standing on anything
		if (!groundBehavior->isOnGround())
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->movementCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->controlState = PlatformerEntity::ControlState::Swimming;

		// Clear current animation
		this->entity->getAnimations()->playAnimation();
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->movementCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entity->controlState = PlatformerEntity::ControlState::Normal;

		// Animate jumping out of water
		if (this->movementCollision->getVelocity().y > 0.0f && this->entity->getStateOrDefaultFloat(StateKeys::MovementY, 0.0f) > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->movementCollision->setVelocity(Vec2(this->movementCollision->getVelocity().x, EntityMovementCollisionBehavior::WaterJumpVelocity));

			this->entity->getAnimations()->playAnimation(this->entity->getJumpAnimation(), SmartAnimationNode::AnimationPlayMode::ReturnToIdle, 0.85f);
		}
		else
		{
			if (this->entity->getAnimations()->getCurrentAnimation() == this->entity->getSwimAnimation())
			{
				this->entity->getAnimations()->clearAnimationPriority();
			}

			this->entity->getAnimations()->playAnimation();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityMovementCollisionBehavior::buildWallDetectors()
{
	const Size wallDetectorSize = Size(std::max(this->entity->getEntitySize().width / 2.0f - 8.0f, 16.0f), std::max(this->entity->getEntitySize().height - 32.0f, 16.0f));

	this->leftCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 1.0f, 8.0f, 0.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);
	this->rightCollision = CollisionObject::create(
		CollisionObject::createCapsulePolygon(wallDetectorSize, 1.0f, 8.0f, 0.0f),
		(int)PlatformerCollisionType::WallDetector,
		false,
		false
	);

	this->leftCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->rightCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof }, [=](CollisionObject::CollisionData collisionData)
	{	
		return CollisionObject::CollisionResult::DoNothing;
	});

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Size entitySize = this->entity->getEntitySize();

	if (this->entity->isFlippedY())
	{
		Vec2 offsetLeft = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(-entitySize.width / 2.0f + wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);
		Vec2 offsetRight = Vec2(collisionOffset.x, -collisionOffset.y) - Vec2(entitySize.width / 2.0f - wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);
		this->leftCollision->inverseGravity();
		this->rightCollision->inverseGravity();
		this->leftCollision->getPhysicsBody()->setPositionOffset(offsetLeft);
		this->rightCollision->getPhysicsBody()->setPositionOffset(offsetRight);
	}
	else
	{
		Vec2 offsetLeft = collisionOffset + Vec2(-entitySize.width / 2.0f + wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);
		Vec2 offsetRight = collisionOffset + Vec2(entitySize.width / 2.0f - wallDetectorSize.width / 2.0f, entitySize.height / 2.0f + this->entity->getHoverHeight() / 2.0f);
		this->leftCollision->getPhysicsBody()->setPositionOffset(offsetLeft);
		this->rightCollision->getPhysicsBody()->setPositionOffset(offsetRight);
	}

	this->addChild(this->leftCollision);
	this->addChild(this->rightCollision);
}

void EntityMovementCollisionBehavior::tryBind()
{
	if (this->movementCollision != nullptr && !this->movementCollisionBound)
	{
		this->movementCollisionBound = true;
		this->movementCollision->bindTo(this->entity);
	}
}
