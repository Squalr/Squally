#include "MineCart.h"

#include "cocos/base/CCValue.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Utils/GameUtils.h"

#include "Resources/ObjectResources.h"

using namespace cocos2d;

const std::string MineCart::MapKey = "mine-cart";
const std::string MineCart::PropertyColor = "color";
const std::string MineCart::PropertyDirection = "direction";

MineCart* MineCart::create(cocos2d::ValueMap& properties)
{
	MineCart* instance = new MineCart(properties);

	instance->autorelease();

	return instance;
}

MineCart::MineCart(cocos2d::ValueMap& properties) : super(properties, Size(128.0f, 96.0f))
{
	this->parseColor();
	this->parseDirection();
	this->body = Sprite::create(this->cartColor == CartColor::Brown ? ObjectResources::Interactive_MineCarts_Body1 : ObjectResources::Interactive_MineCarts_Body2);
	this->wheelFront = Sprite::create(ObjectResources::Interactive_MineCarts_WheelFront);
	this->wheelBack = Sprite::create(ObjectResources::Interactive_MineCarts_WheelBack);
	this->isMoving = false;

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

	wheelBack->setPosition(Vec2(-32.0f, -64.0f));
	wheelFront->setPosition(Vec2(32.0f, -69.0f));
}

void MineCart::update(float dt)
{
	super::update(dt);

	this->moveCart(dt);
}

void MineCart::mount(PlatformerEntity* interactingEntity)
{
	super::mount(interactingEntity);

	this->isMoving = true;
}

void MineCart::dismount()
{
	super::dismount();
	
	this->isMoving = false;
}

Vec2 MineCart::getReparentPosition()
{
	return Vec2::ZERO;
}

void MineCart::moveCart(float dt)
{
	if (!this->isMoving)
	{
		return;
	}

	const float CartSpeed = 768.0f;

	switch(this->cartDirection)
	{
		case CartDirection::Left:
		{
			this->setPosition(this->getPosition() - Vec2(CartSpeed * dt, 0.0f));
			break;
		}
		default:
		case CartDirection::Right:
		{
			this->setPosition(this->getPosition() + Vec2(CartSpeed * dt, 0.0f));
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
