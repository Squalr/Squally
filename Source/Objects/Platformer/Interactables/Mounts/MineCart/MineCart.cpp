#include "MineCart.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntities.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineCart::MapKey = "mine-cart";
const std::string MineCart::PropertyColor = "color";
const std::string MineCart::PropertyDirection = "direction";
const std::string MineCart::PropertySpeed = "speed";

MineCart* MineCart::create(cocos2d::ValueMap& properties)
{
	MineCart* instance = new MineCart(properties);

	instance->autorelease();

	return instance;
}

MineCart::MineCart(cocos2d::ValueMap& properties) : super(properties, Size(240.0f, 184.0f))
{
	this->parseColor();
	this->parseDirection();
	this->cartSpeed = GameUtils::getKeyOrDefault(this->properties, MineCart::PropertySpeed, Value(512.0f)).asFloat();
	this->body = Sprite::create(this->cartColor == CartColor::Brown ? ObjectResources::Interactive_MineCarts_Body1 : ObjectResources::Interactive_MineCarts_Body2);
	this->wheelFront = Sprite::create(ObjectResources::Interactive_MineCarts_WheelFront);
	this->wheelBack = Sprite::create(ObjectResources::Interactive_MineCarts_WheelBack);
	this->isMoving = false;
	this->bottomCollision = CollisionObject::create(
		CollisionObject::createBox(Size(240.0f, 48.0f)),
		int(PlatformerCollisionType::PassThrough),
		CollisionObject::Properties(false, false)
	);

	this->frontNode->addChild(this->bottomCollision);
	this->frontNode->addChild(this->body);
	this->frontNode->addChild(this->wheelFront);
	this->frontNode->addChild(this->wheelBack);
}

MineCart::~MineCart()
{
}

void MineCart::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();
}

void MineCart::initializePositions()
{
	super::initializePositions();

	this->bottomCollision->setPositionY(-96.0f);
	this->wheelBack->setPosition(Vec2(-32.0f, -64.0f));
	this->wheelFront->setPosition(Vec2(32.0f, -69.0f));
}

void MineCart::initializeListeners()
{
	super::initializeListeners();
	

	this->interactCollision->whenCollidesWith({ (CollisionType)PlatformerCollisionType::CartStop }, [=](CollisionObject::CollisionData collisionData)
	{
		this->reverse();
		this->dismount();
		
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});
}

void MineCart::update(float dt)
{
	super::update(dt);

	this->moveCart(dt);
	this->faceEntityTowardsDirection();
}

void MineCart::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->faceEntityTowardsDirection();

	this->isMoving = true;
}

void MineCart::dismount()
{
	super::dismount();
	
	this->isMoving = false;
}

void MineCart::reverse()
{
	switch(this->cartDirection)
	{
		case CartDirection::Left:
		{
			this->setCartDirection(CartDirection::Right);
			break;
		}
		default:
		case CartDirection::Right:
		{
			this->setCartDirection(CartDirection::Left);
			break;
		}
	}
}

void MineCart::faceEntityTowardsDirection()
{
	if (this->mountedEntity == nullptr)
	{
		return;
	}

	switch(this->cartDirection)
	{
		case CartDirection::Left:
		{
			this->mountedEntity->getAnimations()->setFlippedX(true);
			break;
		}
		default:
		case CartDirection::Right:
		{
			this->mountedEntity->getAnimations()->setFlippedX(false);
			break;
		}
	}
}

void MineCart::setCartDirection(CartDirection cartDirection)
{
	this->cartDirection = cartDirection;
}

Vec2 MineCart::getReparentPosition()
{
	return Vec2(0.0f, 128.0f);
}

void MineCart::moveCart(float dt)
{
	if (!this->isMoving)
	{
		return;
	}

	switch(this->cartDirection)
	{
		case CartDirection::Left:
		{
			this->setPosition(this->getPosition() - Vec2(this->cartSpeed * dt, 0.0f));
			break;
		}
		default:
		case CartDirection::Right:
		{
			this->setPosition(this->getPosition() + Vec2(this->cartSpeed * dt, 0.0f));
			break;
		}
	}
}

void MineCart::parseDirection()
{
	std::string direction = GameUtils::getKeyOrDefault(this->properties, MineCart::PropertyDirection, Value("")).asString();

	if (direction == "left")
	{
		this->cartDirection = CartDirection::Left;
	}
	else // if (color == "right")
	{
		this->cartDirection = CartDirection::Right;
	}
}

void MineCart::parseColor()
{
	std::string color = GameUtils::getKeyOrDefault(this->properties, MineCart::PropertyColor, Value("")).asString();

	if (color == "blue")
	{
		this->cartColor = CartColor::Blue;
	}
	else // if (color == "brown")
	{
		this->cartColor = CartColor::Brown;
	}
}
