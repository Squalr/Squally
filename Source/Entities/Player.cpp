#include "Player.h"

Vec2 Player::position;
int Player::health;

Player* Player::create()
{
	Player* player = new Player();

	player->autorelease();

	return player;
}

Player::Player()
{
	this->pressedKeys = std::unordered_map<EventKeyboard::KeyCode, bool>();
	this->sprite = Sprite::create(Resources::Ingame_Sprites_Player_Idle);
	this->collisionObject = CollisionObject::create(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->collisionObject);

	this->InitializeKeyMap();
	this->InitializeListeners();
}

Player::~Player()
{
}

void Player::update(float dt)
{
	Entity::update(dt);

	/*

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		//if (canjump)
		//if (this->physicsBody->getVelocity().y > -4.0f && this->physicsBody->getVelocity().y < 4.0f)
	{
		canJump = false;
		//this->physicsBody->setVelocity(Vec2(this->physicsBody->getVelocity().x, Player::jumpSpeed));
	}
	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		this->sprite->setFlippedX(false);
		//this->physicsBody->setVelocity(Vec2(-Player::walkSpeed, this->physicsBody->getVelocity().y));
		break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		//this->physicsBody->setVelocity(Vec2(this->physicsBody->getVelocity().x, -Player::jumpSpeed));
		break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		this->sprite->setFlippedX(true);
		this->setPositionX(this->getPositionX() + Player::walkSpeed);
		//this->physicsBody->setVelocity(Vec2(Player::walkSpeed, this->physicsBody->getVelocity().y));
		break;
	}
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		//	if (this->physicsBody->getVelocity().y > 0.0f)
	{
		//	this->physicsBody->setVelocity(Vec2(this->physicsBody->getVelocity().x, 0.0f));
	}
	break;
	case EventKeyboard::KeyCode::KEY_LEFT_ARROW:
	case EventKeyboard::KeyCode::KEY_A:
		//	if (this->physicsBody->getVelocity().x < 0.0f)
	{
		//	this->physicsBody->setVelocity(Vec2(0.0f, this->physicsBody->getVelocity().y));
	}
	break;
	case EventKeyboard::KeyCode::KEY_DOWN_ARROW:
	case EventKeyboard::KeyCode::KEY_S:
		//	if (this->physicsBody->getVelocity().y < 0.0f)
	{
		//	this->physicsBody->setVelocity(Vec2(this->physicsBody->getVelocity().x, 0.0f));
	}
	break;
	case EventKeyboard::KeyCode::KEY_RIGHT_ARROW:
	case EventKeyboard::KeyCode::KEY_D:
		//if (this->physicsBody->getVelocity().x > 0.0f)
	{
		//	this->physicsBody->setVelocity(Vec2(0.0f, this->physicsBody->getVelocity().y));
	}
	break;
	}
	*/

	this->position = this->getPosition();
}

void Player::InitializeKeyMap()
{
	this->pressedKeys[EventKeyboard::KeyCode::KEY_SPACE] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_W] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_A] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_S] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_D] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_UP_ARROW] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_LEFT_ARROW] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_DOWN_ARROW] = false;
	this->pressedKeys[EventKeyboard::KeyCode::KEY_RIGHT_ARROW] = false;
}

void Player::InitializeListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	// contactListener->onContactBegin = CC_CALLBACK_1(Player::OnContactBegin, this);

	listener->onKeyPressed = CC_CALLBACK_2(Player::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::OnKeyReleased, this);

	// this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Player::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys[keyCode] = true;
}

void Player::OnKeyReleased(EventKeyboard::KeyCode keyCode, Event* event)
{
	pressedKeys[keyCode] = false;
}
