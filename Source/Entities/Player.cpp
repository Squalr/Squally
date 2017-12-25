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
	this->physicsBody = PhysicsBody::createBox(this->sprite->getContentSize());
	this->physicsBody->setRotationEnable(false);
	this->physicsBody->setContactTestBitmask(Collision::CollisionGroup::All);

	this->addChild(this->sprite);
	this->setPhysicsBody(this->physicsBody);
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
		this->movement.y = 1.0f;
	}

	if (this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->IsPressed(EventKeyboard::KeyCode::KEY_S))
	{
	}
}
