#include "Squally.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/CameraTrackingData.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/HackableEvents.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/SaveEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Input/MouseState.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/Combat/Attacks/Punch.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

using namespace cocos2d;

const float Squally::SquallyScale = 0.92f;
const std::string Squally::MapKeySqually = "squally";

Squally* Squally::create()
{
	ValueMap emptyProperties = ValueMap();
	Squally* instance = new Squally(emptyProperties);

	instance->autorelease();
	
	return instance;
}

Squally* Squally::deserialize(ValueMap& properties)
{
	Squally* instance = new Squally(properties);

	instance->autorelease();
	
	return instance;
}

Squally::Squally(ValueMap& properties) : super(properties,
	Squally::MapKeySqually,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	Size(128.0f, 128.0f),
	Squally::SquallyScale,
	Vec2(0.0f, 24.0f),
	96.0f,
	SaveKeys::SaveKeySquallyInventory,
	SaveKeys::SaveKeySquallyEquipment,
	SaveKeys::SaveKeySquallyCurrencyInventory)
{
	this->cameraTrackTarget = Node::create();

	this->registerHackables();
	this->registerAttack(Punch::create(0.4f, 0.5f));

	this->addChild(this->cameraTrackTarget);
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	this->loadSaveState();

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

void Squally::initializePositions()
{
	super::initializePositions();

	this->cameraTrackTarget->setPosition(Vec2(0.0f, 128.0f));
}

void Squally::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(SaveEvents::EventSoftSaveGameState, [=](EventCustom* eventCustom)
	{
		this->saveState();
	}));

	this->addEventListener(EventListenerCustom::create(PlatformerEvents::EventWarpToLocation, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::WarpArgs* args = static_cast<PlatformerEvents::WarpArgs*>(eventCustom->getUserData());
		
		if (args != nullptr)
		{
			this->setPosition(args->position);
			GameCamera::getInstance()->setCameraPositionToTrackedTarget();
		}
	}));

	this->whenKeyPressedHackerMode({ EventKeyboard::KeyCode::KEY_TAB, EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		args->handle();

		HackableEvents::TriggerHackerModeToggle(HackableEvents::HackToggleArgs(this->getStateOrDefaultInt(StateKeys::Eq, 1)));
	});
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

void Squally::performSwimAnimation()
{
	if (this->equipmentInventory->getWeapon() != nullptr)
	{
		this->animationNode->playAnimation("SwimWithWeapon");
	}
	else
	{
		this->animationNode->playAnimation("Swim");
	}
}

void Squally::onHackerModeEnable(int eq)
{
	super::onHackerModeEnable(eq);
}

void Squally::saveState()
{
}

void Squally::loadSaveState()
{
	/*
	this->setPosition(Vec2(
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionX, Value(this->getPositionX())).asFloat(),
		SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyPositionY, Value(this->getPositionY())).asFloat()
	));
	*/

	// Save new defaults
	this->saveState();
}
