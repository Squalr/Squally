#include "Squally.h"

#include "Engine/Animations/AnimationPart.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Input/Input.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Entities/Platformer/Misc/DaemonsHallow/FlyBot.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Events/NavigationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/Inventory/Items/Equipment/Weapons/Weapon.h"
#include "Scenes/Platformer/Inventory/PlayerCurrencyInventory.h"
#include "Scenes/Platformer/Inventory/PlayerEquipment.h"
#include "Scenes/Platformer/Inventory/PlayerInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const float Squally::squallyScale = 0.92f;
const std::string Squally::MapKeySqually = "squally";
const int Squally::SquallyBaseHealth = 16;
const int Squally::SquallyBaseSpecial = 8;

Squally* Squally::deserialize(ValueMap& properties)
{
	Squally* instance = new Squally(properties);

	instance->autorelease();
	
	return instance;
}

Squally::Squally(ValueMap& properties) : super(properties,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	PlatformerCollisionType::Player,
	Size(128.0f, 128.0f),
	Squally::squallyScale,
	Vec2(0.0f, 24.0f),
	Squally::SquallyBaseHealth,
	Squally::SquallyBaseSpecial,
	Size(128.0f, 224.0f))
{
	this->noCombatDuration = 0.0f;
	this->cameraTrackTarget = Node::create();

	this->registerHackables();
	this->registerAttack(Punch::create(0.4f, 0.5f));

	this->currencyInventory = PlayerCurrencyInventory::getInstance();
	this->inventory = PlayerInventory::getInstance();

	this->addChild(this->cameraTrackTarget);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	this->noCombatDuration = 2.0f;

	this->loadState();
	this->updateWeaponVisual();

	// Request camera track player
	CameraTrackingData trackingData = CameraTrackingData(this->cameraTrackTarget, Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData, true);
}

void Squally::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	// Request HUD track player
	PlatformerEvents::TriggerHudTrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
}

void Squally::onExit()
{
	super::onExit();

	PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
}

void Squally::initializeCollisionEvents()
{
	super::initializeCollisionEvents();

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Enemy, (int)PlatformerCollisionType::EnemyFlying }, [=](CollisionObject::CollisionData collisionData)
	{
		if (this->noCombatDuration > 0.0f)
		{
			return CollisionObject::CollisionResult::DoNothing;
		}

		this->noCombatDuration = 2.0f;
		this->saveState();
		
		PlatformerEnemy* enemy = dynamic_cast<PlatformerEnemy*>(collisionData.other->getParent());

		if (enemy != nullptr && !enemy->isDead() && enemy->getBattleMapResource() != "")
		{
			// TODO: First strike detection
			NavigationEvents::navigateCombat(NavigationEvents::NavigateCombatArgs(
				true,
				enemy->getUniqueIdentifier(),
				enemy->getBattleMapResource(),
				enemy->getBattleMapArgs(),
				{ Squally::MapKeySqually, SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyHelperName, Value(FlyBot::MapKeyFlyBot)).asString() },
				enemy->getCombatEntityList()));
		}

		return CollisionObject::CollisionResult::DoNothing;
	});

	this->entityCollision->whenCollidesWith({ (int)PlatformerCollisionType::Damage, }, [=](CollisionObject::CollisionData collisionData)
	{
		this->setPosition(this->spawnCoords);
		this->entityCollision->setPosition(Vec2::ZERO);
		this->movementCollision->setPosition(Vec2::ZERO);

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
}

void Squally::initializePositions()
{
	super::initializePositions();

	this->cameraTrackTarget->setPosition(Vec2(0.0f, 128.0f));
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

float Squally::getFloatHeight()
{
	return 64.0f;
}

cocos2d::Vec2 Squally::getAvatarFrameOffset()
{
	return Vec2(0.0f, 0.0f);
}

void Squally::update(float dt)
{
	super::update(dt);

	if (this->noCombatDuration > 0.0f)
	{
		this->noCombatDuration -= dt;
	}

	if (this->isCinimaticHijacked || this->getIsPlatformerDisabled())
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

	if (this->movement != Vec2::ZERO)
	{
		// Soft save the player's position
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX()));
		SaveManager::softSaveProfileData(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY()));
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

void Squally::onHackerModeEnable()
{
	super::onHackerModeEnable();
}

void Squally::saveState()
{
	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeySquallyHeath, Value(this->getHealth()) },
		{ SaveKeys::SaveKeySquallyMana, Value(this->getMana()) },
		{ SaveKeys::SaveKeySquallyRunes, Value(this->getRunes()) }
	});
}

void Squally::loadState()
{
	// Note: We just use the current value by default. This is normally the max if Squally was just constructed, but might also
	// Be a lower value (ie if created as injured for a cutscene)
	this->setHealth(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyHeath, Value(this->getHealth())).asInt());
	this->setMana(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(this->getMana())).asInt());
	this->setRunes(SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyMana, Value(this->getRunes())).asInt());
	
	this->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX())).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY())).asFloat()
	));

	// Save new defaults
	this->saveState();
}

void Squally::updateWeaponVisual()
{
	Weapon* weapon = PlayerEquipment::getInstance()->getWeapon();

	if (weapon != nullptr)
	{
		AnimationPart* mainhand = this->getAnimations()->getAnimationPart("mainhand");
		
		if (mainhand != nullptr)
		{
			mainhand->replaceSprite(weapon->getIconResource());
			mainhand->setOffset(weapon->getDisplayOffset());
		}
	}
}
