#include "Squally.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/NavigationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Basic/BasicSlash.h"
#include "Scenes/Platformer/Inventory/Items/Consumables/Health/HealthPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Consumables/Mana/ManaPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Consumables/Speed/SpeedPotion.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Axes/BlueAxe.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Maces/CrystalMace.h" // Debugging
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Swords/CrystalSword.h" // Debugging
#include "Scenes/Platformer/Inventory/PlayerCurrencyInventory.h"
#include "Scenes/Platformer/Inventory/PlayerEquipment.h"
#include "Scenes/Platformer/Inventory/PlayerInventory.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const float Squally::squallyScale = 0.92f;
const std::string Squally::MapKeySqually = "squally";
const int Squally::SquallyBaseHealth = 16;
const int Squally::SquallyBaseSpecial = 8;

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
	this->cameraTrackTarget = Node::create();
	this->hoverCollision = CollisionObject::create(PlatformerEntity::createCapsulePolygon(Size(112.0f, 128.0f), Squally::squallyScale), (int)PlatformerCollisionType::PlayerHover, true, false);
	this->hoverCollision->getPhysicsBody()->setPositionOffset(Vec2(0.0f, 0.0f));
	this->hoverCollision->forceBindTo(this, 8.0f);

	this->registerHackables();
	this->registerAttack(BasicSlash::create(1.5f, 0.15f));

	this->currencyInventory = PlayerCurrencyInventory::getInstance();
	this->inventory = PlayerInventory::getInstance();

	this->addChild(this->hoverCollision);
	this->addChild(this->cameraTrackTarget);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	// Request camera track player
	CameraTrackingData trackingData = CameraTrackingData(this->cameraTrackTarget, Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData);

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

	PlayerEquipment::getInstance()->tryRemove(PlayerEquipment::getInstance()->getWeapon(), nullptr, nullptr);
	PlayerEquipment::getInstance()->forceInsert(CrystalMace::create());
	Weapon* weapon = PlayerEquipment::getInstance()->getWeapon();

	AnimationPart* mainhand = this->getAnimations()->getAnimationPart("mainhand");
	
	mainhand->replaceSprite(weapon->getIconResource());
	mainhand->setOffset(weapon->getDisplayOffset());
}

void Squally::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Request HUD track player
	PlatformerEvents::TriggerHudTrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
}

void Squally::initializeCollisionEvents()
{
	super::initializeCollisionEvents();

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionObject::CollisionData collisionData)
	{
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());

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
		this->entityCollision->setPosition(Vec2::ZERO);
		this->hoverCollision->setPosition(Vec2::ZERO);

		return CollisionObject::CollisionResult::DoNothing;
	});
	
	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		AnimationPart* mouth = this->getAnimations()->getAnimationPart("mouth");
		
		mouth->replaceSprite(EntityResources::Squally_MOUTH_SWIMMING);

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenStopsCollidingWith({ (int)PlatformerCollisionType::Water, }, [=](CollisionObject::CollisionData collisionData)
	{
		AnimationPart* mouth = this->getAnimations()->getAnimationPart("mouth");

		mouth->replaceSprite(EntityResources::Squally_MOUTH);

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

	this->cameraTrackTarget->setPosition(Vec2(0.0f, 128.0f));
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

cocos2d::Vec2 Squally::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Squally::update(float dt)
{
	super::update(dt);

	if (this->isCinimaticHijacked)
	{
		return;
	}

	this->movement = Vec2::ZERO;

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_LEFT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_A))
	{
		this->movement.x = -1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_RIGHT_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_D))
	{
		this->movement.x = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_UP_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_W) || Input::isPressed(EventKeyboard::KeyCode::KEY_SPACE))
	{
		this->movement.y = 1.0f;
	}

	if (Input::isPressed(EventKeyboard::KeyCode::KEY_DOWN_ARROW) || Input::isPressed(EventKeyboard::KeyCode::KEY_S))
	{
		this->movement.y = -1.0f;
	}
}

void Squally::performSwimAnimation()
{
	if (PlayerEquipment::getInstance()->getWeapon() != nullptr)
	{
		this->animationNode->playAnimation("SwimWithWeapon");
	}
	else
	{
		this->animationNode->playAnimation("Swim");
	}
}
