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
#include "Scenes/Platformer/AttachedBehavior/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float Squally::SquallyScale = 0.92f;
const std::string Squally::MapKey = "squally";
const std::string Squally::BattleTag = "squally-team";

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
	Squally::MapKey,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	Size(128.0f, 128.0f),
	Squally::SquallyScale,
	Vec2(0.0f, 24.0f),
	96.0f)
{
}

Squally::~Squally()
{
}

void Squally::onEnter()
{
	super::onEnter();
}

void Squally::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();
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

cocos2d::Vec2 Squally::getDialogueOffset()
{
	return Vec2(0.0f, -16.0f);
}

LocalizedString* Squally::getEntityName()
{
	return Strings::Platformer_Entities_Names_Squally::create();
}

std::string Squally::getSwimAnimation()
{
	std::string swimAnimation = super::getSwimAnimation();

	this->getAttachedBehavior<EntityInventoryBehavior>([&](EntityInventoryBehavior* entityInventoryBehavior)
	{
		if (entityInventoryBehavior->getEquipmentInventory()->getWeapon() != nullptr)
		{
			swimAnimation = "SwimWithWeapon";
		}
		else
		{
			swimAnimation = "Swim";
		}
	});

	return swimAnimation;
}

std::string Squally::getJumpSound()
{
	return SoundResources::Platformer_Entities_Generic_Movement_Jump3;
}

std::vector<std::string> Squally::getWalkSounds()
{
	return { };
}
