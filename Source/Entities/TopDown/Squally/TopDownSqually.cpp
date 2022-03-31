#include "TopDownSqually.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Events/SceneEvents.h"
#include "Engine/Input/Input.h"
#include "Engine/Save/SaveManager.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Components/Entities/Inventory/EntityInventoryBehavior.h"
#include "Scenes/Platformer/Inventory/EquipmentInventory.h"

#include "Resources/EntityResources.h"
#include "Resources/SoundResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const float TopDownSqually::TopDownSquallyScale = 1.0f;
const std::string TopDownSqually::MapKey = "squally-topdown";
const std::string TopDownSqually::TeamTag = "squally-team";

TopDownSqually* TopDownSqually::create()
{
	ValueMap emptyProperties = ValueMap();
	TopDownSqually* instance = new TopDownSqually(emptyProperties);

	instance->autorelease();
	
	return instance;
}

TopDownSqually* TopDownSqually::deserialize(ValueMap& properties)
{
	TopDownSqually* instance = new TopDownSqually(properties);

	instance->autorelease();
	
	return instance;
}

TopDownSqually::TopDownSqually(ValueMap& properties) : super(properties,
	TopDownSqually::MapKey,
	EntityResources::Squally_Animations,
	EntityResources::Squally_Emblem,
	CSize(256.0f, 256.0f),
	TopDownSqually::TopDownSquallyScale,
	Vec2(0.0f, 24.0f),
	96.0f)
{
}

TopDownSqually::~TopDownSqually()
{
}

void TopDownSqually::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(SceneEvents::EventBeforeSceneChange, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::TriggerHudUntrackEntity(PlatformerEvents::HudTrackEntityArgs(this));
	}));
}

Vec2 TopDownSqually::getButtonOffset()
{
	return Vec2(0, 72.0f);
}

cocos2d::Vec2 TopDownSqually::getDialogueOffset()
{
	return Vec2(0.0f, 32.0f);
}

LocalizedString* TopDownSqually::getEntityName()
{
	return Strings::Platformer_Entities_Names_Squally::create();
}

std::vector<std::string> TopDownSqually::getWalkSounds()
{
	return { };
}
