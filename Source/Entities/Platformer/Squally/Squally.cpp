#include "Squally.h"

#include "Engine/Input/Input.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/NavigationEvents.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

Squally* Squally::squallyInstance = nullptr;
int Squally::health;
const float Squally::squallyScale = 0.85f;

const std::string Squally::MapKeySqually = "squally";

Squally* Squally::deserialize(ValueMap* initProperties)
{
	Squally* instance = new Squally(initProperties);

	Squally::squallyInstance = instance;
	instance->autorelease();
	
	return instance;
}

Squally* Squally::getInstance()
{
	return Squally::squallyInstance;
}

Squally::Squally(ValueMap* initProperties) : PlatformerEntity::PlatformerEntity(initProperties,
	EntityResources::Squally_Animations,
	PlatformerCollisionType::Force,
	Size(128.0f, 224.0f), 
	Squally::squallyScale,
	Vec2(0.0f, 48.0f))
{
	this->actualJumpLaunchVelocity = 1280.0f;
	this->actualGravityAcceleration = 400.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 14000.0f;

	this->squallyCollision = CollisionObject::create(PhysicsBody::createCircle(72.0f * Squally::squallyScale, PHYSICSBODY_MATERIAL_DEFAULT, Vec2(0.0f, 72.0f * Squally::squallyScale)), (int)PlatformerCollisionType::Player, false, false);

	this->registerHackables();

	this->addChild(this->squallyCollision);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	PlatformerEntity::onEnter();
}

void Squally::initializeCollisionEvents()
{
	PlatformerEntity::initializeCollisionEvents();

	this->squallyCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionData collisionData)
	{
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other);

		if (enemy != nullptr)
		{
			NavigationEvents::navigateCombat(NavigationEvents::NavigateCombatArgs(enemy->getBattleMapResource(), this, enemy));
		}

		return CollisionResult::DoNothing;
	});

	this->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});

	this->squallyCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionData collisionData)
	{
		return CollisionResult::DoNothing;
	});
}

void Squally::registerHackables()
{
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

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void Squally::update(float dt)
{
	PlatformerEntity::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x -= 1.0f;
		this->setFlippedX(true);
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x += 1.0f;
		this->setFlippedX(false);
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W) || Input::isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y += 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		// TODO: Hover height magic (probably just by scaling the main physicsbody)
	}
}

void Squally::setFlippedX(bool newIsFlipped)
{
	this->isFlipped = newIsFlipped;
}

Size Squally::getSize()
{
	return this->size * Squally::squallyScale;
}
