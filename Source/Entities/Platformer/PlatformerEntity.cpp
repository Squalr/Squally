#include "PlatformerEntity.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Platformer/Attacks/PlatformerAttack.h"

#include "Resources/UIResources.h"

const float PlatformerEntity::groundCollisionDetectorPadding = 12.0f;
const float PlatformerEntity::groundCollisionDetectorOffset = 2.0f;
const float PlatformerEntity::capsuleRadius = 8.0f;
const float PlatformerEntity::groundDragFactor = .58f;
const float PlatformerEntity::airDragFactor = 0.65f;
const float PlatformerEntity::maxMoveSpeed = 360.0f;
const float PlatformerEntity::maxJumpSpeed = 720.0f;
const float PlatformerEntity::maxFallSpeed = -1280.0f;

const int PlatformerEntity::FallBackMaxHealth = 10;
const int PlatformerEntity::FallBackMaxSpecial = 10;
const int PlatformerEntity::MaxRunes = 4;

using namespace cocos2d;

PlatformerEntity::PlatformerEntity(
	ValueMap* initProperties, 
	std::string scmlResource, 
	PlatformerCollisionType collisionType,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial
	) : super(
		initProperties,
		PlatformerEntity::createCapsulePolygon(size, scale),
		(CollisionType)(int)collisionType,
		true,
		false
	)
{
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->groundCollisionDetector = CollisionObject::create(
		PhysicsBody::createBox(
			Size(std::max((size * scale).width - PlatformerEntity::groundCollisionDetectorPadding * 2.0f, 8.0f), 8.0f),
			PHYSICSBODY_MATERIAL_DEFAULT
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);
	this->speechBubble = SpeechBubble::create();
	this->attacks = std::vector<PlatformerAttack*>();
	this->groundCollisions = std::set<CollisionObject*>();
	this->spawnCoords = this->getPosition();
	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);

	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 1280.0f;
	this->moveAcceleration = 14000.0f;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");

	float height = (*this->properties)[PlatformerEntity::MapKeyHeight].asFloat();

	this->setPositionY(this->getPositionY());

	this->getPhysicsBody()->setPositionOffset(Vec2(0.0f, (size * scale).height / 2.0f) - Vec2(0.0f, height / 2.0f));
	this->groundCollisionDetector->getPhysicsBody()->setPositionOffset(Vec2(0.0f, -PlatformerEntity::groundCollisionDetectorOffset) - Vec2(0.0f, height / 2.0f));
	this->animationNode->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	animationNode->setPosition(collisionOffset * scale - Vec2(0.0f, height / 2.0f));

	this->clickHitbox->setContentSize(size);
	this->clickHitbox->setOffsetCorrection(Vec2(0.0f, this->clickHitbox->getContentSize().height / 2.0f));

	// Update width to be serialized
	if (this->properties != nullptr)
	{
		(*this->properties)[PlatformerEntity::MapKeyWidth] = size.width * scale;
		(*this->properties)[PlatformerEntity::MapKeyHeight] = size.height * scale;
	}

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipX))
	{
		this->animationNode->setFlippedX((*this->properties)[PlatformerEntity::MapKeyWidth].asBool());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipY))
	{
		this->animationNode->setFlippedY((*this->properties)[PlatformerEntity::MapKeyWidth].asBool());
	}

	this->maxHealth = baseHealth;
	this->maxSpecial = baseSpecial;

	this->health = this->maxHealth;
	this->special = this->maxSpecial;
	this->runes = PlatformerEntity::MaxRunes;

	this->animationNode->addChild(this->clickHitbox);
	this->addChild(this->groundCollisionDetector);
	this->addChild(this->animationNode);
	this->addChild(this->speechBubble);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	CollisionObject::onEnter();

	this->scheduleUpdate();
}

void PlatformerEntity::initializePositions()
{
	CollisionObject::initializePositions();

	this->speechBubble->setPositionY(((*this->properties)[PlatformerEntity::MapKeyHeight].asFloat() * this->getScaleY()) / 2.0f);
}

void PlatformerEntity::initializeListeners()
{
	CollisionObject::initializeListeners();

	this->initializeCollisionEvents();
}

void PlatformerEntity::update(float dt)
{
	CollisionObject::update(dt);

	Vec2 velocity = this->getVelocity();

	velocity.x += this->movement.x * PlatformerEntity::moveAcceleration * dt;

	if (this->isOnGround())
	{
		velocity.x *= PlatformerEntity::groundDragFactor;
	}
	else
	{
		velocity.x *= PlatformerEntity::airDragFactor;
	}

	// Gravity
	if (this->movement.y > 0.0f && this->isOnGround())
	{
		this->groundCollisions.clear();

		velocity.y = this->movement.y * this->actualJumpLaunchVelocity;

		this->animationNode->playAnimation("Jump");
	}

	// Prevent fast speeds
	velocity.x = MathUtils::clamp(velocity.x, -PlatformerEntity::maxMoveSpeed, PlatformerEntity::maxMoveSpeed);
	velocity.y = MathUtils::clamp(velocity.y, PlatformerEntity::maxFallSpeed, PlatformerEntity::maxJumpSpeed);

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

int PlatformerEntity::getHealth()
{
	return this->health;
}

int PlatformerEntity::getMaxHealth()
{
	return this->maxHealth;
}

int PlatformerEntity::getSpecial()
{
	return this->health;
}

int PlatformerEntity::getMaxSpecial()
{
	return this->maxHealth;
}

int PlatformerEntity::getRunes()
{
	return this->runes;
}

int PlatformerEntity::getMaxRunes()
{
	return PlatformerEntity::MaxRunes;
}

std::vector<PlatformerAttack*> PlatformerEntity::getAttacks()
{
	return this->attacks;
}

std::vector<PlatformerAttack*> PlatformerEntity::cloneAttacks()
{
	std::vector<PlatformerAttack*> attacksClone = std::vector<PlatformerAttack*>();

	for (auto it = this->attacks.begin(); it != this->attacks.end(); it++)
	{
		attacksClone.push_back((*it)->clone());
	}

	return attacksClone;
}

bool PlatformerEntity::isOnGround()
{
	return (!this->groundCollisions.empty());
}

void PlatformerEntity::initializeCollisionEvents()
{
	this->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionData collisionData)
	{
		return CollisionResult::CollideWithPhysics;
	});

	this->groundCollisionDetector->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionData collisionData)
	{
		this->groundCollisions.insert(collisionData.other);

		return CollisionResult::DoNothing;
	});

	this->groundCollisionDetector->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionData collisionData)
	{
		if (this->groundCollisions.find(collisionData.other) != this->groundCollisions.end())
		{
			this->groundCollisions.erase(collisionData.other);
		}

		return CollisionResult::DoNothing;
	});
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

void PlatformerEntity::registerAttack(PlatformerAttack* attack)
{
	attack->retain();
	this->attacks.push_back(attack);
}
