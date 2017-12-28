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
	this->hoverNode = Node::create();

	this->init(PhysicsBody::createBox(this->sprite->getContentSize()), CollisionGroup::G_Player, CollisionGroup::SET_Player);
	this->hoverPhysicsBody = PhysicsBody::createBox(Size(this->sprite->getContentSize().width, Player::hoverHeight));

	this->hoverNode->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->hoverNode->setPosition(0, -this->sprite->getContentSize().height / 2);
	this->hoverNode->setContentSize(Size(0, Player::hoverHeight));

	this->hoverPhysicsBody->setRotationEnable(false);
	this->hoverPhysicsBody->setGravityEnable(false);

	FiniteTimeAction* bounceY1 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 0.25f));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 1.0f));

	this->hoverNode->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));

	this->hoverNode->setPhysicsBody(this->hoverPhysicsBody);

	this->addChild(this->sprite);
	this->addChild(this->hoverNode);
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
		this->hoverNode->setScaleY(0.1f);
	}

	// Keep hover node underneath player
	this->hoverNode->setPosition(0, -this->sprite->getContentSize().height / 2 + 1.0f);
	this->hoverPhysicsBody->setVelocity(this->getVelocity());
}
