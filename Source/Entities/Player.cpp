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
	this->inputManager = InputManager::GetInstance();
	this->sprite = Sprite::create(Resources::Ingame_Sprites_Player_Idle);
	this->collisionObject = CollisionObject::create(this->sprite->getContentSize());

	this->addChild(this->sprite);
	this->addChild(this->collisionObject);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	Entity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
		this->sprite->setFlippedX(false);
	}

	if (this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
		this->sprite->setFlippedX(true);
	}

	if (this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_W) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->velocity.y = this->jumpSpeed;
	}

	if (this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_S))
	{
	}

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
