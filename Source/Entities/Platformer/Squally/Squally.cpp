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
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"

#include "Strings/Platformer/Entities/Names/Squally.h"

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
	this->registerHackables();
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();

	// Request camera track player
	CameraTrackingData trackingData = CameraTrackingData(this, Vec2(0.0f, 128.0f), Vec2(128.0f, 96.0f));
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
}

void Squally::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
	}));
}

void Squally::update(float dt)
{
	super::update(dt);
}

Vec2 Squally::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

float Squally::getFloatHeight()
{
	return 64.0f;
}

cocos2d::Vec2 Squally::getDialogueOffset()
{
	return Vec2(0.0f, 0.0f);
}

LocalizedString* Squally::getEntityName()
{
	return Strings::Platformer_Entities_Names_Squally::create();
}

void Squally::performSwimAnimation()
{
	if (this->equipmentInventory->getWeapon() != nullptr)
	{
		this->animationNode->playAnimation("SwimWithWeapon", SmartAnimationNode::AnimationPlayMode::Repeat, 0.75f);
	}
	else
	{
		this->animationNode->playAnimation("Swim", SmartAnimationNode::AnimationPlayMode::Repeat, 0.75f);
	}
}

void Squally::onHackerModeEnable(int hackFlags)
{
	super::onHackerModeEnable(hackFlags);
}
