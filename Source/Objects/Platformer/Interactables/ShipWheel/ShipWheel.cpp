#include "ShipWheel.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Inventory/Item.h"
#include "Engine/Inventory/MinMaxPool.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/DialogueEvents.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/ItemPools/RecipePools/RecipePoolDeserializer.h"
#include "Scenes/Platformer/Inventory/Items/Recipes/Recipe.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Objectives/ObjectiveKeys.h"
#include "Scenes/Platformer/Objectives/Objectives.h"
#include "Scenes/Platformer/State/StateKeys.h"

#include "Resources/ObjectResources.h"
#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string ShipWheel::MapKey = "ship-wheel";

ShipWheel* ShipWheel::create(ValueMap& properties)
{
	ShipWheel* instance = new ShipWheel(properties);

	instance->autorelease();

	return instance;
}

ShipWheel::ShipWheel(ValueMap& properties) : super(properties, InteractObject::InteractType::Input, CSize(112.0f, 148.0f))
{
	this->neck = Sprite::create(ObjectResources::Interactive_ShipWheel_Neck);
	this->wheel = Sprite::create(ObjectResources::Interactive_ShipWheel_Wheel);
	
	this->addChild(this->neck);
	this->addChild(this->wheel);
}

ShipWheel::~ShipWheel()
{
}

void ShipWheel::initializePositions()
{
	super::initializePositions();
	
	const float offsetY = -24.0f;
	this->neck->setPosition(Vec2(0.0f, offsetY));
	this->wheel->setPosition(Vec2(0.0f, 92.0f + offsetY));
}

void ShipWheel::onInteract(PlatformerEntity* interactingEntity)
{
	super::onInteract(interactingEntity);

	this->showCharterShipOptions();
}

void ShipWheel::showCharterShipOptions()
{
	std::vector<LocalizedString*> options = std::vector<LocalizedString*>();
	std::vector<std::function<bool()>> callbacks = std::vector<std::function<bool()>>();
	
	options.push_back(Strings::Platformer_MapNames_DataMines_Drammol::create());
	options.push_back(Strings::Platformer_MapNames_DataMines_DataMines::create());
	options.push_back(Strings::Platformer_MapNames_EndianForest_Elbridge::create());
	options.push_back(Strings::Menus_Cancel::create());

	callbacks.push_back([=]()
	{
		this->steeringWheelWarp(MapResources::DataMines_Zone_3_8);
		Objectives::SetCurrentObjective(ObjectiveKeys::DMRestorePower);
		return true;
	});

	callbacks.push_back([=]()
	{
		this->steeringWheelWarp(MapResources::DataMines_Zone_3_7);
		return true;
	});

	callbacks.push_back([=]()
	{
		this->steeringWheelWarp(MapResources::EndianForest_Town_Docks);
		return true;
	});

	callbacks.push_back([=]()
	{
		DialogueEvents::TriggerTryDialogueClose(DialogueEvents::DialogueCloseArgs([=]()
		{
		}));
		return true;
	});

	DialogueEvents::TriggerOpenDialogue(DialogueEvents::DialogueOpenArgs(
		DialogueEvents::BuildOptions(Strings::Platformer_Dialogue_Recruitable_RecruitableChoose::create(), options),
		DialogueEvents::DialogueVisualArgs(
			DialogueBox::DialogueDock::Bottom,
			DialogueBox::DialogueAlignment::Left,
			DialogueEvents::BuildPreviewNode(&this->scrappy, false),
			DialogueEvents::BuildPreviewNode(nullptr, true)
		),
		[=]()
		{
		},
		"",
		true,
		false,
		callbacks,
		[=](){ return true; }
	));
}

void ShipWheel::steeringWheelWarp(std::string mapFile)
{
	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
	{
		PlatformerEvents::TriggerBeforePlatformerMapChange();
		PlatformerMap* map = PlatformerMap::create("charter-ship");
		
		map->loadMap(mapFile);

		return map;
	}));
}
