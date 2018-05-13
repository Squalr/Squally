#include "Player.h"

Vec2 Player::position;
int Player::health;
const float Player::playerScale = 0.13f;

Player* Player::create()
{
	Player* instance = new Player();

	instance->autorelease();

	return instance;
}

Player::Player() : Entity::Entity(Resources::Entities_Player_Animations, false, Size(720.0f, 1600.0f), Player::playerScale, Vec2(0.0f, 600.0f))
{
	this->actualJumpLaunchVelocity = 640.0f;
	this->actualGravityAcceleration = 400.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 14000.0f;

	this->inputManager = InputManager::getInstance();

	this->init(PhysicsBody::createBox(size * Player::playerScale, PhysicsMaterial(0.0f, 0.0f, 0.0f)), CategoryGroup::G_Player, true, false);
	// this->hover = Hover::create(this);

	//this->hover->setContactBeginCallback(CC_CALLBACK_1(Player::hoverContactBegin, this));
	//this->hover->setContactUpdateCallback(CC_CALLBACK_1(Player::hoverContactUpdate, this));
	//this->hover->setContactEndCallback(CC_CALLBACK_1(Player::hoverContactEnd, this));
	//this->addChild(this->hover);

	// TODO: Load from save
	this->equipWand(Wand::Stick);

	this->registerHackables();
}

Player::~Player()
{
}

void Player::registerHackables()
{
	this->setButtonOffset(Vec2(0, 72.0f));

	//HackableData* hackableDataHealth = HackableData::create("Health", &this->health, &typeid(this->health));
	//HackableData* hackableDataPositionX = HackableData::create("X Position", &this->position.x, &typeid(this->position.x));
	//HackableData* hackableDataPositionY = HackableData::create("Y Position", &this->position.y, &typeid(this->position.y));

	//HackableCode* hackableVelocity = HackableCode::create("Take Damage", &this->_displayedColor, 8);
	//HackableCode* hackableVelocityA = HackableCode::create("Set X Velocity", &this->_actionManager, 4);
	//HackableCode* hackableVelocityB = HackableCode::create("Set Y Velocity", &this->_scaleX, 7);

	//this->registerData(hackableDataHealth);
	//this->registerData(hackableDataPositionX);
	//this->registerData(hackableDataPositionY);

	//this->registerCode(hackableVelocity);
	//this->registerCode(hackableVelocityA);
	//this->registerCode(hackableVelocityB);
}

void Player::update(float dt)
{
	Entity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
		this->setFlippedX(true);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
		this->setFlippedX(false);
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_W) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y = 1.0f;
	}

	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->hover->setHeight(16.0f);
	}

	// TODO: Prolly break this out to a radial menu
	if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_1))
	{
		this->equipWand(Wand::Stick);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_2))
	{
		this->equipWand(Wand::Snake);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_3))
	{
		this->equipWand(Wand::Ancient);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_4))
	{
		this->equipWand(Wand::Spider);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_5))
	{
		this->equipWand(Wand::Crystal);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_6))
	{
		this->equipWand(Wand::Dragon);
	}
	else if (this->inputManager->isPressed(EventKeyboard::KeyCode::KEY_7))
	{
		this->equipWand(Wand::Skeleton);
	}

	this->position = this->getPosition();
}

void Player::equipWand(Wand wand)
{
	this->setFlippedX(this->isFlipped);
}

void Player::setFlippedX(bool newIsFlipped)
{
	this->isFlipped = newIsFlipped;
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
	switch (data.other->getCategoryGroup())
	{
	case CategoryGroup::G_Enemy:
	case CategoryGroup::G_EnemyFlying:
		Enemy * enemy = dynamic_cast<Enemy*>(data.other);

		if (enemy != nullptr)
		{
			NavigationEvents::loadFight(this, enemy);
		}

		return false;
	}

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

Size Player::getSize()
{
	return this->size * Player::playerScale;
}
