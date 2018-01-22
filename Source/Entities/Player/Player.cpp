#include "Player.h"

Vec2 Player::position;
int Player::health;

Player* Player::create()
{
	Player* player = new Player();

	player->autorelease();

	return player;
}

Player::Player() : Entity::Entity()
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 1000.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 14000.0f;

	this->inputManager = InputManager::getInstance();

	this->sprite = Sprite::create(Resources::Ingame_Sprites_Player_Idle);
	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CategoryGroup::G_Player, true, false);
	this->hover = Hover::create(this);

	this->hover->setContactBeginCallback(CC_CALLBACK_1(Player::hoverContactBegin, this));
	this->hover->setContactUpdateCallback(CC_CALLBACK_1(Player::hoverContactUpdate, this));
	this->hover->setContactEndCallback(CC_CALLBACK_1(Player::hoverContactEnd, this));

	this->addChild(this->sprite);
	this->addChild(this->hover);

	this->registerHackables();
}

Player::~Player()
{
}

void Player::registerHackables()
{
	this->setPreviewImage(Resources::Menus_HackerModeMenu_WireFrames_SquallyWireFrame);
	this->setButtonOffset(Vec2(0, 72.0f));
}

void Player::update(float dt)
{
	Entity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
		this->sprite->setFlippedX(true);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
		this->sprite->setFlippedX(false);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_W) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y = 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->hover->setHeight(16.0f);
	}

	this->position = this->getPosition();
}

bool Player::hoverContactBegin(CollisionData data)
{
	return true;
}

bool Player::hoverContactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		if (abs(data.normal.y) >= Entity::normalJumpThreshold)
		{
			this->isOnGround = true;
		}
		return true;
	case CategoryGroup::G_Player:
		return true;
	}

	return true;
}

bool Player::hoverContactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		this->isOnGround = false;
		return true;
	case CategoryGroup::G_Player:
		return true;
	}

	return true;
}

bool Player::contactBegin(CollisionData data)
{
	return true;
}

bool Player::contactUpdate(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		switch (data.direction)
		{
		case CollisionDirection::Down:
			this->isOnGround = true;
			break;
		}
		return true;
	case CategoryGroup::G_Force:
		return true;
	case CategoryGroup::G_Enemy:
	case CategoryGroup::G_EnemyFlying:
		// TODO: Damage
		return false;
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		return false;
	}

	return true;
}

bool Player::contactEnd(CollisionData data)
{
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Solid:
		this->isOnGround = false;
		return true;
	case CategoryGroup::G_Force:
		return true;
	case CategoryGroup::G_Enemy:
	case CategoryGroup::G_EnemyFlying:
		return false;
	case CategoryGroup::G_SolidNpc:
	case CategoryGroup::G_SolidFlyingNpc:
		return false;
	}

	return true;
}
