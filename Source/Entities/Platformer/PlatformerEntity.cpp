#include "PlatformerEntity.h"

const float PlatformerEntity::groundCollisionDetectorPadding = 8.0f;
const float PlatformerEntity::groundCollisionDetectorOffset = 24.0f;
const float PlatformerEntity::capsuleRadius = 8.0f;

PlatformerEntity::PlatformerEntity(ValueMap* initProperties, std::string scmlResource, PlatformerCollisionType collisionType, Size size, float scale, Vec2 collisionOffset) :
	CollisionObject(
		initProperties,
		PlatformerEntity::createCapsulePolygon(size, scale),
		(CollisionType)(int)collisionType,
		true,
		false
	)
{
	this->size = size;

	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 1280.0f;
	this->moveAcceleration = 14000.0f;

	this->isOnGround = false;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");

	animationNode->setPosition(collisionOffset * scale);

	// Update width to be serialized
	if (this->properties != nullptr)
	{
		(*this->properties)[PlatformerEntity::MapKeyWidth] = size.width * scale;
		(*this->properties)[PlatformerEntity::MapKeyHeight] = size.height * scale;
	}

	this->groundCollisionDetector = CollisionObject::create(
		PhysicsBody::createBox(
			Size(std::max((size * scale).width - PlatformerEntity::groundCollisionDetectorPadding * 2.0f, 8.0f), 8.0f),
			PHYSICSBODY_MATERIAL_DEFAULT, 
			Vec2(0.0f, -(size * scale).height / 2.0f - PlatformerEntity::groundCollisionDetectorOffset)
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);

	this->addChild(this->groundCollisionDetector);
	this->addChild(this->animationNode);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	CollisionObject::onEnter();

	this->scheduleUpdate();

	this->initializeCollisionEvents();
}

void PlatformerEntity::initializePositions()
{
	CollisionObject::initializePositions();
}

void PlatformerEntity::initializeListeners()
{
	CollisionObject::initializeListeners();
}

void PlatformerEntity::update(float dt)
{
	CollisionObject::update(dt);

	Vec2 velocity = this->getVelocity();

	velocity.x += this->movement.x * PlatformerEntity::moveAcceleration * dt;

	if (this->isOnGround)
	{
		velocity.x *= PlatformerEntity::groundDragFactor;
	}
	else
	{
		velocity.x *= PlatformerEntity::airDragFactor;
	}

	// Gravity
	if (this->isOnGround)
	{
		if (this->movement.y > 0.0f)
		{
			velocity.y = this->movement.y * this->actualJumpLaunchVelocity;
			this->isOnGround = false;

			this->animationNode->playAnimation("Jump");
		}
	}

	// Prevent fast speeds
	velocity.x = MathUtils::clamp(velocity.x, -this->maxMoveSpeed, this->maxMoveSpeed);
	velocity.y = MathUtils::clamp(velocity.y, -this->maxFallSpeed, this->maxFallSpeed);

	// Apply velocity
	this->setVelocity(velocity);

	// Update flip
	if (this->animationNode != nullptr)
	{
		if (this->movement.x < 0.0f)
		{
			this->animationNode->setFlippedX(true);
		}
		else if (this->movement.x > 0.0f)
		{
			this->animationNode->setFlippedX(false);
		}
	}
}

void PlatformerEntity::initializeCollisionEvents()
{
	this->groundCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionData collisionData)
	{
		this->isOnGround = true;

		return CollisionResult::DoNothing;
	});

	this->groundCollisionDetector->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionData collisionData)
	{
		this->isOnGround = false;

		return CollisionResult::DoNothing;
	});
}

Size PlatformerEntity::getSize()
{
	return this->size;
}

PhysicsBody* PlatformerEntity::createCapsulePolygon(Size size, float scale)
{
	Size newSize = size * scale;

	newSize.height = std::max(0.0f, newSize.height - PlatformerEntity::capsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(newSize.width / 2.0f, newSize.height / 2.0f));
	points.push_back(Vec2(newSize.width / 2.0f, -newSize.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -newSize.height / 2.0f - PlatformerEntity::capsuleRadius));

	// Left side
	points.push_back(Vec2(-newSize.width / 2.0f, -newSize.height / 2.0f));
	points.push_back(Vec2(-newSize.width / 2.0f, newSize.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, newSize.height / 2.0f + PlatformerEntity::capsuleRadius));

	return PhysicsBody::createPolygon(points.data(), points.size());
}