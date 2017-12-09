#include "Player.h"
#include "Resources.h"
#include "cocos2d.h"

using namespace cocos2d;

static int health;

Player::Player()
{
	Entity::Entity();

	this->sprite = Sprite::create(Resources::Sprites_Player_Idle);
	this->physicsBody = PhysicsBody::createCircle(this->sprite->getContentSize().width);
	this->physicsBody->setDynamic(false);

	this->addChild(this->sprite);
	this->setPhysicsBody(this->physicsBody);
}

Player::~Player()
{
	delete(this->sprite);
}

void Player::onEnter()
{
	Entity::onEnter();

	this->InitializeListeners();
}

void Player::update(float dt)
{
	Entity::update(dt);
}

void Player::InitializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();
	listener->onKeyPressed = CC_CALLBACK_2(Player::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::OnKeyReleased, this);

	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		this->sprite->setFlippedX(false);
		this->physicsBody->setVelocity(Vec2(-Player::walkSpeed, this->physicsBody->getVelocity().y));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		this->sprite->setFlippedX(true);
		this->physicsBody->setVelocity(Vec2(Player::walkSpeed, this->physicsBody->getVelocity().y));
		break;
	}
}

void Player::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		if (this->physicsBody->getVelocity().x < 0.0f)
		{
			this->physicsBody->setVelocity(Vec2(0.0f, this->physicsBody->getVelocity().y));
		}
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		if (this->physicsBody->getVelocity().x > 0.0f)
		{
			this->physicsBody->setVelocity(Vec2(0.0f, this->physicsBody->getVelocity().y));
		}
		break;
	}
}
