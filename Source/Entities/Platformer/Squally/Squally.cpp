#include "Squally.h"

#include "Engine/Input/Input.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Basic/BasicSlash.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/NavigationEvents.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const float Squally::squallyScale = 0.85f;
const std::string Squally::MapKeySqually = "squally";
const int Squally::SquallyBaseHealth = 25;
const int Squally::SquallyBaseSpecial = 15;

Squally* Squally::deserialize(ValueMap& initProperties)
{
	Squally* instance = new Squally(initProperties);

	instance->autorelease();
	
	return instance;
}

Squally::Squally(ValueMap& initProperties) : super(initProperties,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	PlatformerCollisionType::Force,
	Size(128.0f, 224.0f), 
	Squally::squallyScale,
	Vec2(0.0f, 72.0f),
	Squally::SquallyBaseHealth,
	Squally::SquallyBaseSpecial)
{
	this->actualJumpLaunchVelocity = 1280.0f;
	this->actualGravityAcceleration = 400.0f;
	this->actualMaxFallSpeed = 600.0f;
	this->moveAcceleration = 14000.0f;

	this->squallyCollisionDefaultPosition = Vec2(0.0f, 48.0f * Squally::squallyScale);

	this->squallyCollision = CollisionObject::create(PhysicsBody::createCircle(72.0f * Squally::squallyScale, PHYSICSBODY_MATERIAL_DEFAULT, Vec2::ZERO), (int)PlatformerCollisionType::Player, false, false);
	this->squallyCollision->getPhysicsBody()->setPositionOffset(this->getPhysicsBody()->getPositionOffset());
	this->squallyCollision->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->registerHackables();
	this->registerAttack(BasicSlash::create(1.5f, 0.15f));

	this->addChild(this->squallyCollision);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();
}

void Squally::initializeCollisionEvents()
{
	super::initializeCollisionEvents();

	this->squallyCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionData collisionData)
	{
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other);

		if (enemy != nullptr && !enemy->isDead() && enemy->getBattleMapResource() != "")
		{
			// TODO: First strike detection
			NavigationEvents::navigateCombat(NavigationEvents::NavigateCombatArgs(true, enemy->getUniqueIdentifier(), enemy->getBattleMapResource(), { Squally::MapKeySqually }, enemy->getCombatEntityList()));
		}

		return CollisionResult::DoNothing;
	});

	this->squallyCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionData collisionData)
	{
		this->setPosition(this->spawnCoords);

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

void Squally::initializePositions()
{
	super::initializeListeners();

	this->squallyCollision->setPosition(this->squallyCollisionDefaultPosition);
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

void Squally::update(float dt)
{
	super::update(dt);

	this->movement.x = 0.0f;
	this->movement.y = 0.0f;

	// Handle case where physics acts on Squally's physics body (which is separate)
	Vec2 squallyDelta = this->squallyCollision->getPosition() - this->squallyCollisionDefaultPosition;

	if (squallyDelta != Vec2::ZERO)
	{
		this->setPosition(this->getPosition() + squallyDelta);

		this->squallyCollision->setPosition(this->squallyCollisionDefaultPosition);
	}

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
		// TODO: Hover height crouch (resize/scale physicsbody)
	}
}

void Squally::setFlippedX(bool newIsFlipped)
{
	this->isFlipped = newIsFlipped;
}
