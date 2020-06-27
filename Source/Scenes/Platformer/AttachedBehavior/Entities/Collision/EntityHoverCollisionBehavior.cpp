#include "EntityHoverCollisionBehavior.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityCollisionBehaviorBase.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityGroundCollisionBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Collision/EntityJumpCollisionBehavior.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

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
	this->hoverGroundCollisionDetector = nullptr;
	this->hoverJumpCollisionDetector = nullptr;

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
	
	this->defer([=]()
	{
		this->buildHoverGroundCollision();
		this->buildHoverJumpCollision();
		this->buildHoverCollision();
		this->toggleQueryable(true);
	});
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
}

bool EntityHoverCollisionBehavior::isOnGround()
{
	return (this->hoverGroundCollisionDetector == nullptr ? false : !this->hoverGroundCollisionDetector->getCurrentCollisions().empty());
}

bool EntityHoverCollisionBehavior::canJump()
{
	return (this->hoverJumpCollisionDetector == nullptr ? false : !this->hoverJumpCollisionDetector->getCurrentCollisions().empty());
}

void EntityHoverCollisionBehavior::buildHoverGroundCollision()
{
	if (this->hoverGroundCollisionDetector != nullptr || this->entity->getHoverHeight() <= 0.0f)
	{
		return;
	}

	float detectorWidth = std::max((this->entity->getEntitySize()).width + EntityGroundCollisionBehavior::GroundCollisionPadding * 2.0f, 8.0f);

	this->hoverGroundCollisionDetector = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(detectorWidth, EntityGroundCollisionBehavior::GroundCollisionHeight)
		),
		(int)PlatformerCollisionType::GroundDetector,
		CollisionObject::Properties(false, false),
		Color4F::GRAY
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, -this->entity->getEntitySize().height / 2.0f - this->entity->getHoverHeight() / 2.0f + EntityGroundCollisionBehavior::GroundCollisionOffset / 2.0f);

	this->hoverGroundCollisionDetector->setPosition(offset);

	this->addChild(this->hoverGroundCollisionDetector);

	this->hoverGroundCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::SolidRoof, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->groundCollision != nullptr)
		{
			this->groundCollision->onCollideWithGround();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->hoverGroundCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Intersection }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityHoverCollisionBehavior::buildHoverJumpCollision()
{
	if (this->hoverJumpCollisionDetector != nullptr || this->entity->getHoverHeight() <= 0.0f)
	{
		return;
	}

	this->hoverJumpCollisionDetector = CollisionObject::create(
		CollisionObject::createCapsulePolygon(
			Size(std::max((this->entity->getEntitySize()).width - EntityJumpCollisionBehavior::JumpCollisionMargin * 2.0f, 8.0f), EntityJumpCollisionBehavior::JumpCollisionHeight)
		),
		(int)PlatformerCollisionType::JumpDetector,
		CollisionObject::Properties(false, false),
		Color4F::YELLOW
	);

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, -this->entity->getEntitySize().height / 2.0f - this->entity->getHoverHeight() / 2.0f + EntityJumpCollisionBehavior::JumpCollisionHeight / 2.0f);

	this->hoverJumpCollisionDetector->setPosition(offset);

	this->addChild(this->hoverJumpCollisionDetector);

	this->hoverJumpCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->groundCollision != nullptr)
		{
			this->groundCollision->onCollideWithGround();
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void EntityHoverCollisionBehavior::buildHoverCollision()
{
	if (this->hoverCollision != nullptr || this->entity->getHoverHeight() <= 0.0f)
	{
		return;
	}

	Size hoverSize = Size(this->entity->getEntitySize().width /*std::min(this->entity->getEntitySize().width / 2.0f, 24.0f)*/, this->entity->getHoverHeight());

	CollisionType collisionType = CollisionType(PlatformerCollisionType::Hover);

	this->hoverCollision = CollisionObject::create(
		CollisionObject::createBox(hoverSize),
		// CollisionObject::createCapsulePolygon(hoverSize, 8.0f),
		collisionType,
		CollisionObject::Properties(false, false),
		Color4F::BLUE
	);
	
	this->hoverCollision->setName("entity movement");

	Vec2 collisionOffset = this->entity->getCollisionOffset();
	Vec2 offset = collisionOffset + Vec2(0.0f, -hoverSize.height / 2.0f);

	this->hoverCollision->setPosition(offset);

	this->addChild(this->hoverCollision);

	this->entity->watchForAttachedBehavior<EntityCollisionBehaviorBase>([=](EntityCollisionBehaviorBase* entityCollision)
	{
		this->hoverCollision->setCorrectionRedirectionTarget(entityCollision->movementCollision);
	});
	
	this->hoverCollision->whileCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::SolidPlayerOnly }, [=](CollisionObject::CollisionData collisionData)
	{
		static const Vec2 HoverSpeed = Vec2(0.0f, 192.0f);
		static const float MinSpeed = -64.0f;
		
		/*
		if (this->hoverGroundCollisionDetector->getCurrentCollisions().size() == 1)
		{
			return CollisionObject::CollisionResult::CollideWithPhysics;
		}
		*/

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
