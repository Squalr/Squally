#include "Player.h"

Player::Player()
{
	Entity::Entity();

	this->sprite = Sprite::create(Resources::Sprites_Player_Idle);
	this->physicsBody = PhysicsBody::createCircle(this->sprite->getContentSize().width / 2, PhysicsMaterial(1.0f, 1.0f, 1.0f));
	this->physicsBody->setRotationEnable(false);
	this->physicsBody->setContactTestBitmask(TileCollision::CollisionGroupsEnum::Entity);

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
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	contactListener->onContactBegin = CC_CALLBACK_1(Player::OnContactBegin, this);
	contactListener->onContactPostSolve = CC_CALLBACK_1(Player::OnContactPostSolve, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(Player::OnContactPreSolve, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Player::OnContactSeparate, this);

	listener->onKeyPressed = CC_CALLBACK_2(Player::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::OnKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Player::OnContactBegin(PhysicsContact &contact)
{
	if (contact.getShapeA()->getBody()->getNode() != this && contact.getShapeB()->getBody()->getNode() != this)
	{
		return true;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody()->getNode() == this)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	switch (other->getContactTestBitmask())
	{
	case TileCollision::CollisionGroupsEnum::Solid:
		return true;
	case TileCollision::CollisionGroupsEnum::Water:
		this->physicsBody->setLinearDamping(8.0f);
		return false;
	case TileCollision::CollisionGroupsEnum::PassThrough:
		if (this->physicsBody->getVelocity().y > 0)
		{
			return false;
		}
		return true;
	default:
		return true;
	}
}

bool Player::OnContactPostSolve(PhysicsContact &contact)
{
	if (contact.getShapeA()->getBody()->getNode() != this && contact.getShapeB()->getBody()->getNode() != this)
	{
		return true;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody()->getNode() == this)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	switch (other->getContactTestBitmask())
	{
	case TileCollision::CollisionGroupsEnum::Solid:
		return true;
	case TileCollision::CollisionGroupsEnum::Water:
		this->physicsBody->setLinearDamping(2.0f);
		return false;
	case TileCollision::CollisionGroupsEnum::PassThrough:
		if (this->physicsBody->getVelocity().y > 0)
		{
			return false;
		}
		return true;
	default:
		return true;
	}
}

bool Player::OnContactPreSolve(PhysicsContact &contact)
{
	if (contact.getShapeA()->getBody()->getNode() != this && contact.getShapeB()->getBody()->getNode() != this)
	{
		return true;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody()->getNode() == this)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	switch (other->getContactTestBitmask())
	{
	case TileCollision::CollisionGroupsEnum::Solid:
		return true;
	case TileCollision::CollisionGroupsEnum::Water:
		this->physicsBody->setLinearDamping(2.0f);
		return false;
	case TileCollision::CollisionGroupsEnum::PassThrough:
		if (this->physicsBody->getVelocity().y > 0)
		{
			return false;
		}
		return true;
	default:
		return true;
	}
}

bool Player::OnContactSeparate(PhysicsContact &contact)
{
	if (contact.getShapeA()->getBody()->getNode() != this && contact.getShapeB()->getBody()->getNode() != this)
	{
		return true;
	}

	PhysicsShape* other = nullptr;

	if (contact.getShapeA()->getBody()->getNode() == this)
	{
		other = contact.getShapeB();
	}
	else
	{
		other = contact.getShapeA();
	}

	switch (other->getContactTestBitmask())
	{
	case TileCollision::CollisionGroupsEnum::Solid:
		return true;
	case TileCollision::CollisionGroupsEnum::Water:
		this->physicsBody->setLinearDamping(2.0f);
		return false;
	case TileCollision::CollisionGroupsEnum::PassThrough:
		if (this->physicsBody->getVelocity().y > 0)
		{
			return false;
		}
		return true;
	default:
		return true;
	}
}

void Player::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_SPACE:
	case EventKeyboard::KeyCode::KEY_UP_ARROW:
	case EventKeyboard::KeyCode::KEY_W:
		// if (canjump)
		if (this->physicsBody->getVelocity().y > -4.0f && this->physicsBody->getVelocity().y < 4.0f)
		{
			canJump = false;
			this->physicsBody->setVelocity(Vec2(this->physicsBody->getVelocity().x, Player::jumpSpeed));
		}
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
	case EventKeyboard::KeyCode::KEY_SPACE:
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
