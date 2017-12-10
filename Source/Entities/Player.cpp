#include "Player.h"
#include "Resources.h"
#include "../Collision/CollisionGroups.h"
#include "cocos2d.h"

using namespace cocos2d;

static int health;

bool canJump;

Player::Player()
{
	Entity::Entity();

	this->sprite = Sprite::create(Resources::Sprites_Player_Idle);
	this->physicsBody = PhysicsBody::createCircle(this->sprite->getContentSize().width / 2, PhysicsMaterial(0.0f, 0.0f, 0.0f));
	this->physicsBody->setRotationEnable(false);
	this->physicsBody->setContactTestBitmask(CollisionGroups::CollisionGroupsEnum::Entity);

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
	listener->onKeyPressed = CC_CALLBACK_2(Player::OnKeyPressed, this);
	listener->onKeyReleased = CC_CALLBACK_2(Player::OnKeyReleased, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

bool Player::OnContactBegin(PhysicsContact &contact)
{
	Node* nodeA = contact.getShapeA()->getBody()->getNode();
	Node* nodeB = contact.getShapeB()->getBody()->getNode();

	if (nodeA != this && nodeB != this)
	{
		return true;
	}

	for (int index = 0; index < size(contact.getContactData()->points); index++)
	{
		Vec2 contactPoint = contact.getContactData()->points[index];

		float end = this->getPositionX() + this->GetWidth();
		float x = this->getPositionX();
		float y = this->getPositionY();

		if (contactPoint.y > y)
		{
			canJump = true;
		}
	}

	return true;
}

void Player::OnKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	switch (keyCode)
	{
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
