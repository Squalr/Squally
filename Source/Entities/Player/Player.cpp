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
	this->inputManager = InputManager::getInstance();

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Player_Idle);
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CollisionGroup::G_Player, CollisionGroup::HELPER_Player);
	this->hover = Hover::create(this);

	this->hover->setContactBeginCallback(CC_CALLBACK_1(Player::hoverContactBegin, this));
	this->hover->setContactUpdateCallback(CC_CALLBACK_1(Player::hoverContactUpdate, this));
	this->hover->setContactEndCallback(CC_CALLBACK_1(Player::hoverContactEnd, this));

	this->addChild(this->sprite);
	this->addChild(this->hover);
}

Player::~Player()
{
}

void Player::update(float dt)
{
	Entity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
		this->sprite->setFlippedX(false);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
		this->sprite->setFlippedX(true);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_W) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y = 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->hover->setHeight(16.0f);
	}
}

bool Player::contactBegin(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		if (data.isCollisionBelow)
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::contactUpdate(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		if (data.isCollisionBelow)
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::contactEnd(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		this->isOnGround = false;
		break;
	}

	return true;
}

bool Player::hoverContactBegin(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		if (data.isCollisionBelow)
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::hoverContactUpdate(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		if (data.isCollisionBelow)
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::hoverContactEnd(CollisionData data)
{
	switch (data.other->getCollisionGroup())
	{
	case CollisionGroup::G_Solid:
		this->isOnGround = false;
		break;
	}

	return true;
}
