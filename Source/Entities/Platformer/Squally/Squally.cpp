#include "Squally.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Basic/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CrystalSword.h" // Debugging
#include "Scenes/Platformer/Inventory/PlayerEquipment.h"
#include "Scenes/Platformer/Inventory/PlayerInventory.h"

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
	PlatformerCollisionType::Player,
	Size(128.0f, 128.0f),
	Squally::squallyScale,
	Vec2(0.0f, 24.0f),
	Squally::SquallyBaseHealth,
	Squally::SquallyBaseSpecial)
{
	this->hoverCollision = CollisionObject::create(PlatformerEntity::createCapsulePolygon(Size(112.0f, 128.0f), Squally::squallyScale), (int)PlatformerCollisionType::PlayerHover, true, false);
	this->hoverCollision->getPhysicsBody()->setPositionOffset(Vec2(0.0f, 0.0f));
	this->hoverCollision->forceBindTo(this, 8.0f);

	this->registerHackables();
	this->registerAttack(BasicSlash::create(1.5f, 0.15f));

	this->inventory = PlayerInventory::getInstance();

	this->addChild(this->hoverCollision);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	if (PlayerEquipment::getInstance()->getWeapon() == nullptr)
	{
		PlayerEquipment::getInstance()->forceInsert(CrystalSword::create());
	}

	if (PlayerInventory::getInstance()->getItems().empty())
	{
		PlayerInventory::getInstance()->forceInsert(HealthPotion::create());
		PlayerInventory::getInstance()->forceInsert(ManaPotion::create());
		PlayerInventory::getInstance()->forceInsert(SpeedPotion::create());
	}

	Weapon* weapon = PlayerEquipment::getInstance()->getWeapon();
	AnimationPart* mainhand = this->getAnimations()->getAnimationPart("mainhand");
	
	mainhand->replaceSprite(weapon->getIconResource());
}

void Squally::initializeCollisionEvents()
{
	super::initializeCollisionEvents();

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionObject::CollisionData collisionData)
	{
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other);

		if (enemy != nullptr && !enemy->isDead() && enemy->getBattleMapResource() != "")
		{
			// TODO: First strike detection
			NavigationEvents::navigateCombat(NavigationEvents::NavigateCombatArgs(true, enemy->getUniqueIdentifier(), enemy->getBattleMapResource(), { Squally::MapKeySqually }, enemy->getCombatEntityList()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->setPosition(this->spawnCoords);

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});

	this->hoverCollision->whenCollidesWith({ (int)PlatformerCollisionType::Solid, (int)PlatformerCollisionType::PassThrough }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::CollideWithPhysics;
	});

	this->hoverCollision->whenCollidesWith({ (int)PlatformerCollisionType::FriendlyNpc, }, [=](CollisionObject::CollisionData collisionData)
	{
		return CollisionObject::CollisionResult::DoNothing;
	});
}

void Squally::initializePositions()
{
	super::initializeListeners();
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
