#include "PlatformerEntity.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Dialogue/SpeechBubble.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Inventory/Inventory.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/PlatformerAttack.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const float PlatformerEntity::MoveAcceleration = 14000.0f;
const Vec2 PlatformerEntity::SwimAcceleration = Vec2(8000.0f, 420.0f);
const float PlatformerEntity::SwimVerticalDrag = 0.93f;
const float PlatformerEntity::JumpVelocity = 7680.0f;
const float PlatformerEntity::GroundCollisionPadding = 22.0f;
const float PlatformerEntity::GroundCollisionOffset = 2.0f;
const float PlatformerEntity::CapsuleRadius = 8.0f;

const int PlatformerEntity::FallBackMaxHealth = 10;
const int PlatformerEntity::FallBackMaxMana = 10;
const int PlatformerEntity::MaxRunes = 4;

PlatformerEntity::PlatformerEntity(
	ValueMap& initProperties, 
	std::string scmlResource,
	std::string emblemResource,
	PlatformerCollisionType collisionType,
	Size size,
	float scale, 
	Vec2 collisionOffset,
	int baseHealth,
	int baseSpecial
	) : super(initProperties)
{
	this->animationNode = SmartAnimationNode::create(scmlResource);
	this->emblemResource = emblemResource;
	this->isCinimaticHijacked = false;
	this->entityCollision = CollisionObject::create(
		PlatformerEntity::createCapsulePolygon(size, scale),
		(CollisionType)(int)collisionType,
		true,
		false
	);
	this->groundCollision = CollisionObject::create(
		PhysicsBody::createBox(
			Size(std::max((size * scale).width - PlatformerEntity::GroundCollisionPadding * 2.0f, 8.0f), 8.0f),
			PHYSICSBODY_MATERIAL_DEFAULT
		),
		(int)PlatformerCollisionType::GroundDetector,
		false,
		false
	);
	this->hexusOpponentData = nullptr;
	this->inventory = Inventory::create();
	this->speechBubble = SpeechBubble::create();
	this->attacks = std::vector<PlatformerAttack*>();
	this->spawnCoords = this->getPosition();
	this->clickHitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);
	this->controlState = ControlState::Normal;

	// TODO: Configurable/randomizable start direction (if any)
	this->movement = Vec2(0.0f, 0.0f);

	this->animationNode->setScale(scale);
	this->animationNode->playAnimation("Idle");

	float width = this->properties[PlatformerEntity::MapKeyWidth].asFloat();
	float height = this->properties[PlatformerEntity::MapKeyHeight].asFloat();
	this->entitySize = size * scale;

	this->setPositionY(this->getPositionY());

	this->entityCollision->bindTo(this);
	this->entityCollision->getPhysicsBody()->setLinearDamping(1.0f);
	this->entityCollision->getPhysicsBody()->setPositionOffset(collisionOffset * scale + Vec2(0.0f, (size * scale).height / 2.0f));
	this->groundCollision->getPhysicsBody()->setPositionOffset(Vec2(0.0f, -PlatformerEntity::GroundCollisionOffset) - Vec2(0.0f, height / 2.0f));
	this->animationNode->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->clickHitbox->setContentSize(this->entitySize);
	this->clickHitbox->setPosition(Vec2(0.0f, (size * scale).height / 2.0f) + Vec2((size * scale).width / 2.0f, -height / 2.0f));
	this->clickHitbox->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->clickHitbox->disableInteraction();

	// Update width to be serialized
	this->properties[PlatformerEntity::MapKeyWidth] = size.width * scale;
	this->properties[PlatformerEntity::MapKeyHeight] = size.height * scale;

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipX))
	{
		this->animationNode->setFlippedX(this->properties[PlatformerEntity::MapKeyFlipX].asBool());
	}

	if (GameUtils::keyExists(this->properties, PlatformerEntity::MapKeyFlipY))
	{
		this->animationNode->setFlippedY(this->properties[PlatformerEntity::MapKeyFlipY].asBool());
	}

	this->maxHealth = baseHealth;
	this->maxMana = baseSpecial;

	this->health = this->maxHealth;
	this->mana = this->maxMana;
	this->runes = PlatformerEntity::MaxRunes;

	this->addChild(this->entityCollision);
	this->addChild(this->groundCollision);
	this->addChild(this->animationNode);
	this->addChild(this->speechBubble);
	this->addChild(this->clickHitbox);
	this->addChild(this->inventory);
}

PlatformerEntity::~PlatformerEntity()
{
}

void PlatformerEntity::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void PlatformerEntity::initializePositions()
{
	super::initializePositions();

	this->speechBubble->setPositionY((this->properties[PlatformerEntity::MapKeyHeight].asFloat() * this->getScaleY()) / 2.0f);
}

void PlatformerEntity::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicHijack, [=](EventCustom*)
	{
		this->isCinimaticHijacked = true;
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventCinematicRestore, [=](EventCustom*)
	{
		this->isCinimaticHijacked = false;
	}));

	this->initializeCollisionEvents();
}

void PlatformerEntity::update(float dt)
{
	super::update(dt);

	if (this->isDead())
	{
		this->entityCollision->setVelocity(Vec2::ZERO);
		return;
	}

	if (this->isCinimaticHijacked)
	{
		return;
	}

	Vec2 velocity = this->entityCollision->getVelocity();

	switch (this->controlState)
	{
		default:
		case ControlState::Normal:
		{
			velocity.x += this->movement.x * PlatformerEntity::MoveAcceleration * dt;

			if (this->movement.y > 0.0f && this->isOnGround())
			{
				velocity.y = this->movement.y * PlatformerEntity::JumpVelocity;

				this->performJumpAnimation();
			}

			break;
		}
		case ControlState::Swimming:
		{
			const float minSpeed = PlatformerEntity::SwimAcceleration.y;

			// A lil patch to reduce that "acceleraton" feel of swimming vertical, and instead make it feel more instant
			if (velocity.y < minSpeed && this->movement.y > 0.0f)
			{
				velocity.y = minSpeed;
			}
			else if (velocity.y > -minSpeed && this->movement.y < 0.0f)
			{
				velocity.y = -minSpeed;
			}

			velocity.x += this->movement.x * PlatformerEntity::SwimAcceleration.x * dt;
			velocity.y += this->movement.y * PlatformerEntity::SwimAcceleration.y * dt;

			if (this->movement != Vec2::ZERO)
			{
				this->performSwimAnimation();
			}

			break;
		}
	}
	
	// Apply velocity
	this->entityCollision->setVelocity(velocity);

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

void PlatformerEntity::performSwimAnimation()
{
	this->animationNode->playAnimation("Swim");
}

void PlatformerEntity::performJumpAnimation()
{
	this->animationNode->playAnimation("Jump");
}

void PlatformerEntity::addHealth(int healthDelta)
{
	this->setHealth(this->getHealth() + healthDelta);
}

void PlatformerEntity::setHealth(int health)
{
	if (this->isDead())
	{
		return;
	}

	this->health = MathUtils::clamp(health, 0, this->maxHealth);

	if (this->health <= 0)
	{
		this->animationNode->playAnimation("Death", SmartAnimationNode::AnimationPlayMode::PauseOnAnimationComplete);
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

bool PlatformerEntity::isDead()
{
	return this->health <= 0;
}

int PlatformerEntity::getMana()
{
	return this->mana;
}

int PlatformerEntity::getMaxMana()
{
	return this->maxMana;
}

int PlatformerEntity::getRunes()
{
	return this->runes;
}

int PlatformerEntity::getMaxRunes()
{
	return PlatformerEntity::MaxRunes;
}

SmartAnimationNode* PlatformerEntity::getAnimations()
{
	return this->animationNode;
}

Size PlatformerEntity::getEntitySize()
{
	return this->entitySize;
}

HexusOpponentData* PlatformerEntity::getHexusOpponentData()
{
	return this->hexusOpponentData;
}

CollisionObject* PlatformerEntity::getEntityCollision()
{
	return this->entityCollision;
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

Inventory* PlatformerEntity::getInventory()
{
	return this->inventory;
}

CurrencyInventory* PlatformerEntity::getCurrencyInventory()
{
	return this->currencyInventory;
}

bool PlatformerEntity::isOnGround()
{
	return (!this->groundCollision->getCurrentCollisions().empty());
}

void PlatformerEntity::initializeCollisionEvents()
{
	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entityCollision->setGravityEnabled(false);
		this->controlState = ControlState::Swimming;
		this->entityCollision->setVerticalDampening(PlatformerEntity::SwimVerticalDrag);

		// Clear current animation
		this->animationNode->playAnimation("Idle");
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->entityCollision->setGravityEnabled(true);
		this->controlState = ControlState::Normal;
		this->entityCollision->setVerticalDampening(CollisionObject::DefaultVerticalDampening);

		// Animate jumping out of water
		if (this->entityCollision->getVelocity().y > 0.0f)
		{
			// Give a velocity boost for jumping out of water
			this->entityCollision->setVelocity(Vec2(this->entityCollision->getVelocity().x, PlatformerEntity::JumpVelocity));

			this->animationNode->playAnimation("Jump");
		}
		
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->groundCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		// Clear current animation
		this->animationNode->playAnimation("Idle");

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->groundCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough, (int)PlatformerCollisionType::Physics }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

PhysicsBody* PlatformerEntity::createCapsulePolygon(Size size, float scale)
{
	Size newSize = size * scale;

	newSize.height = std::max(0.0f, newSize.height - PlatformerEntity::CapsuleRadius * 2.0f);

	std::vector<Vec2> points = std::vector<Vec2>();

	// Right side
	points.push_back(Vec2(newSize.width / 2.0f, newSize.height / 2.0f));
	points.push_back(Vec2(newSize.width / 2.0f, -newSize.height / 2.0f));

	// Bottom capsule
	points.push_back(Vec2(0.0f, -newSize.height / 2.0f - PlatformerEntity::CapsuleRadius));

	// Left side
	points.push_back(Vec2(-newSize.width / 2.0f, -newSize.height / 2.0f));
	points.push_back(Vec2(-newSize.width / 2.0f, newSize.height / 2.0f));

	// Top capsule
	points.push_back(Vec2(0.0f, newSize.height / 2.0f + PlatformerEntity::CapsuleRadius));

	return PhysicsBody::createPolygon(points.data(), points.size(), PhysicsMaterial(0.5f, 0.0f, 0.5f));
}

void PlatformerEntity::registerAttack(PlatformerAttack* attack)
{
	this->addChild(attack);
	this->attacks.push_back(attack);
}

std::string PlatformerEntity::getEmblemResource()
{
	return this->emblemResource;
}
