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
	this->hoverNode = Node::create();

	this->physicsBody = PhysicsBody::createBox(this->sprite->getContentSize());
	this->hoverPhysicsBody = PhysicsBody::createBox(Size(this->sprite->getContentSize().width, Player::hoverHeight));

	this->hoverNode->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->hoverNode->setPosition(0, -this->sprite->getContentSize().height / 2);
	this->hoverNode->setContentSize(Size(0, Player::hoverHeight));

	this->physicsBody->setRotationEnable(false);
	this->collisionGroup = Collision::CollisionGroup::Player;
	this->physicsBody->setContactTestBitmask(Collision::CollisionGroup::SET_Player);

	this->hoverPhysicsBody->setRotationEnable(false);
	this->hoverPhysicsBody->setContactTestBitmask(Collision::CollisionGroup::SET_Solids);
	this->hoverPhysicsBody->setGravityEnable(false);

	FiniteTimeAction* bounceY1 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 0.25f));
	FiniteTimeAction* bounceY2 = EaseSineInOut::create(ScaleTo::create(3.0f, 1.0f, 1.0f));

	this->hoverNode->runAction(RepeatForever::create(Sequence::create(bounceY1, bounceY2, nullptr)));

	this->setPhysicsBody(this->physicsBody);
	this->hoverNode->setPhysicsBody(this->hoverPhysicsBody);

	this->addChild(this->sprite);
	this->addChild(this->hoverNode);

	this->InitializeListeners();
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
		this->hoverNode->setScaleY(0.1f);
	}

	// Keep hover node underneath player
	this->hoverNode->setPosition(0, -this->sprite->getContentSize().height / 2 + 1.0f);
	this->hoverPhysicsBody->setVelocity(this->physicsBody->getVelocity());
}

void Player::InitializeListeners()
{
	EventListenerPhysicsContact* contactListener = EventListenerPhysicsContact::create();

	contactListener->onContactBegin = CC_CALLBACK_1(Player::OnContactBegin, this);
	contactListener->onContactPreSolve = CC_CALLBACK_1(Player::OnContactUpdate, this);
	contactListener->onContactSeparate = CC_CALLBACK_1(Player::OnContactEnd, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(contactListener, this);
}

bool Player::OnContactBegin(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->hoverPhysicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	switch ((Collision::CollisionGroup)other->getContactTestBitmask())
	{
	case Collision::CollisionGroup::Solid:
		if (Collision::IsContactBelow(this, contact))
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::OnContactUpdate(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->hoverPhysicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	switch ((Collision::CollisionGroup)other->getContactTestBitmask())
	{
	case Collision::CollisionGroup::Solid:
		if (Collision::IsContactBelow(this, contact))
		{
			this->isOnGround = true;
		}
		break;
	}

	return true;
}

bool Player::OnContactEnd(PhysicsContact &contact)
{
	PhysicsShape* other = Collision::GetCollidingObject(this->hoverPhysicsBody, contact);

	if (other == nullptr)
	{
		return true;
	}

	switch ((Collision::CollisionGroup)other->getContactTestBitmask())
	{
	case Collision::CollisionGroup::Solid:
		this->isOnGround = false;
		break;
	}

	return true;
}