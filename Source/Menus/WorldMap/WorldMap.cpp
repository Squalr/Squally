#include "WorldMap.h"

#include "cocos/base/CCEvent.h"
#include "cocos/2d/CCActionEase.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/Localization/Localization.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Events/NavigationEvents.h"
#include "Menus/WorldMap/FX/Lightning.h"
#include "Menus/WorldMap/FX/LightningSphere.h"
#include "Menus/WorldMap/MapNode.h"

#include "Resources/MapResources.h"
#include "Resources/UIResources.h"

WorldMap* WorldMap::instance = nullptr;

const std::string WorldMap::StringKeySelectLevel = "Menu_Story_Select_Level";
const std::string WorldMap::StringKeyLevelNameJungle = "Menu_Story_Level_Name_Jungle";
const std::string WorldMap::StringKeyLevelNameAquaticRuins = "Menu_Story_Level_Name_Aquatic_Ruins";
const std::string WorldMap::StringKeyLevelNameForest = "Menu_Story_Level_Name_Forest";
const std::string WorldMap::StringKeyLevelNameCaverns = "Menu_Story_Level_Name_Caverns";
const std::string WorldMap::StringKeyLevelNameCastle = "Menu_Story_Level_Name_Castle";
const std::string WorldMap::StringKeyLevelNameIceCaps = "Menu_Story_Level_Name_Ice_Caps";
const std::string WorldMap::StringKeyLevelNameObelisk = "Menu_Story_Level_Name_Obelisk";
const std::string WorldMap::StringKeyLevelNameVolcano = "Menu_Story_Level_Name_Volcano";
const std::string WorldMap::StringKeyLevelNameMech = "Menu_Story_Level_Name_Mech";

void WorldMap::registerGlobalScene()
{
	if (WorldMap::instance == nullptr)
	{
		WorldMap::instance = new WorldMap();

		WorldMap::instance->autorelease();
		WorldMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(WorldMap::instance);
}

WorldMap::WorldMap()
{
	this->mapNodes = std::vector<MapNode*>();
	this->mouse = Mouse::create();
	this->background = Sprite::create(UIResources::Menus_WorldMap_WorldMap);
	this->hud = Hud::create();

	this->forest = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameForest),
		MapResources::EndianForest_Forest
	);

	this->waterRuins = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameAquaticRuins),
		MapResources::UnderflowRuins_AquaticRuins
	);

	this->caverns = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameCaverns),
		MapResources::SeaSharpCaverns_Caverns
	);

	this->castle = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameCastle),
		MapResources::CastleValgrind_Castle
	);

	this->iceCaps = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameIceCaps),
		MapResources::LambdaPeaks_IceCaps
	);

	this->volcano = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameVolcano),
		MapResources::DaemonsHallow_Volcano
	);

	this->crypts = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameObelisk),
		MapResources::LexiconCrypts_Obelisk
	);

	this->voidStar = MapNode::create(
		Localization::resolveString(WorldMap::StringKeyLevelNameMech),
		MapResources::VoidStar_Mech
	);

	this->voidCrystalNode = Node::create();
	this->voidCrystal = Sprite::create(UIResources::Menus_WorldMap_VoidCrystal);
	this->lightningSphere = LightningSphere::create();
	this->lightning1 = Lightning::create();
	this->lightning2 = Lightning::create();
	this->lightning3 = Lightning::create();
	this->lightning4 = Lightning::create();
	this->lightning5 = Lightning::create();
	this->lightning6 = Lightning::create();
	this->lightning7 = Lightning::create();
	this->lightning8 = Lightning::create();
	this->lightning9 = Lightning::create();
	this->lightning10 = Lightning::create();

	this->background->setAnchorPoint(Vec2(0.0f, 0.0f));

	this->hud->addChild(this->mouse);
	this->addChild(this->background);
	this->addChild(this->forest);
	this->addChild(this->waterRuins);
	this->addChild(this->caverns);
	this->addChild(this->castle);
	this->addChild(this->iceCaps);
	this->addChild(this->volcano);
	this->addChild(this->crypts);
	this->addChild(this->voidStar);
	this->addChild(this->voidCrystalNode);
	this->voidCrystalNode->addChild(this->voidCrystal);
	this->voidCrystalNode->addChild(this->lightningSphere);
	this->addChild(this->lightning1);
	this->addChild(this->lightning2);
	this->addChild(this->lightning3);
	this->addChild(this->lightning4);
	this->addChild(this->lightning5);
	this->addChild(this->lightning6);
	this->addChild(this->lightning7);
	this->addChild(this->lightning8);
	this->addChild(this->lightning9);
	this->addChild(this->lightning10);
	this->addChild(this->hud);
}

WorldMap::~WorldMap()
{
}

void WorldMap::onEnter()
{
	GlobalScene::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->background->getContentSize().width, this->background->getContentSize().height));

	CameraTrackingData trackingData = CameraTrackingData(this->mouse, Vec2(480.0f, 270.0f), CameraTrackingData::CameraScrollType::Ellipse);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Because the mouse is a HUD object (and thus unaffected by the camera position), we need a custom function for getting the position to help with camera tracking
	trackingData.customPositionFunction = [=]()
	{
		return this->mouse->getPosition() + GameCamera::getInstance()->getCameraPosition() - visibleSize / 2.0f;
	};

	Vec2 startPosition = this->voidCrystalNode->getPosition();

	this->voidCrystalNode->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(4.0f, startPosition + Vec2(0.0f, -32.0f))),
		EaseSineInOut::create(MoveTo::create(4.0f, startPosition)),
		nullptr
	)));

	GameCamera::getInstance()->setTarget(trackingData);
}

void WorldMap::initializePositions()
{
	GlobalScene::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forest->setPosition(Vec2(visibleSize.width / 2.0f - 503.0f, visibleSize.height / 2.0f + 922.0f));
	this->waterRuins->setPosition(Vec2(visibleSize.width / 2.0f - 552.0f, visibleSize.height / 2.0f + 479.0f));
	this->caverns->setPosition(Vec2(visibleSize.width / 2.0f - 413.0f, visibleSize.height / 2.0f + 81.0f));
	this->castle->setPosition(Vec2(visibleSize.width / 2.0f + 256.0f, visibleSize.height / 2.0f - 50.0f));
	this->iceCaps->setPosition(Vec2(visibleSize.width / 2.0f + 1117.0f, visibleSize.height / 2.0f - 166.0f));
	this->volcano->setPosition(Vec2(visibleSize.width / 2.0f + 1068.0f, visibleSize.height / 2.0f + 679.0f));
	this->crypts->setPosition(Vec2(visibleSize.width / 2.0f + 340.0f, visibleSize.height / 2.0f + 869.0f));
	this->voidStar->setPosition(Vec2(visibleSize.width / 2.0f + 760.0f, visibleSize.height / 2.0f + 268.0f));
	this->voidCrystalNode->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f, visibleSize.height / 2.0f + 584.0f));
	this->lightning1->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f - 128.0f, visibleSize.height / 2.0f + 584.0f + 32.0f));
	this->lightning2->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f - 32.0f, visibleSize.height / 2.0f + 584.0f + 128.0f));
	this->lightning3->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 128.0f, visibleSize.height / 2.0f + 584.0f + 32.0f));
	this->lightning4->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f - 256.0f, visibleSize.height / 2.0f + 584.0f - 64.0f));
	this->lightning5->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 128.0f, visibleSize.height / 2.0f + 584.0f + 72.0f));
	this->lightning6->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 32.0f, visibleSize.height / 2.0f + 584.0f - 128.0f));
	this->lightning7->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 128.0f, visibleSize.height / 2.0f + 584.0f - 128.0f));
	this->lightning8->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 256.0f, visibleSize.height / 2.0f + 584.0f - 64.0f));
	this->lightning9->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 320.0f, visibleSize.height / 2.0f + 584.0f - 256.0f));
	this->lightning10->setPosition(Vec2(visibleSize.width / 2.0f + 512.0f + 64, visibleSize.height / 2.0f + 584.0f - 196.0f));

	this->initializedLocked();
}

void WorldMap::initializeListeners()
{
	GlobalScene::initializeListeners();

	WorldMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateWorldMap, [](EventCustom* args)
	{
		GlobalDirector::loadScene(WorldMap::instance);
	}));

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(WorldMap::onKeyPressed, this);

	this->addEventListener(keyboardListener);
}

void WorldMap::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			event->stopPropagation();
			NavigationEvents::navigateBack();
			break;
		}
		default:
		{
			break;
		}
	}
}

void WorldMap::initializedLocked()
{
	/*
	this->jungle->setLocked(false);
	this->waterRuins->setLocked(false);
	this->forest->setLocked(false);
	this->caverns->setLocked(false);
	this->castle->setLocked(false);
	this->iceCaps->setLocked(false);
	this->obelisk->setLocked(false);
	this->volcano->setLocked(false);
	this->mech->setLocked(false);*/
}
