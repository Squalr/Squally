#include "WorldMap.h"

#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEvent.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/MouseEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Sound/SoundManager.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Platformer/WorldMap/FX/Lightning.h"
#include "Scenes/Platformer/WorldMap/FX/LightningSphere.h"
#include "Scenes/Platformer/WorldMap/MapNode.h"

#include "Resources/MapResources.h"
#include "Resources/MusicResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

WorldMap* WorldMap::instance = nullptr;

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
	this->background = Sprite::create(UIResources::Menus_WorldMap_WorldMap);
	this->hud = Hud::create();

	this->forest = MapNode::create(
		MapResources::EndianForest_Forest
	);

	this->waterRuins = MapNode::create(
		MapResources::UnderflowRuins_AquaticRuins
	);

	this->caverns = MapNode::create(
		MapResources::SeaSharpCaverns_Caverns
	);

	this->castle = MapNode::create(
		MapResources::CastleValgrind_Castle
	);

	this->iceCaps = MapNode::create(
		MapResources::BallmerPeaks_IceCaps
	);

	this->volcano = MapNode::create(
		MapResources::DaemonsHallow_Volcano
	);

	this->crypts = MapNode::create(
		MapResources::LambdaCrypts_Crypts
	);

	this->voidStar = MapNode::create(
		MapResources::VoidStar_VoidStar
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

	if (this->background != nullptr)
	{
		this->background->setAnchorPoint(Vec2(0.0f, 0.0f));
	}

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
	if (this->voidCrystalNode != nullptr)
	{
		this->voidCrystalNode->addChild(this->voidCrystal);
		this->voidCrystalNode->addChild(this->lightningSphere);
	}
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
	super::onEnter();

	const float delay = 0.5f;
	const float duration = 0.75f;

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->background->getContentSize().width, this->background->getContentSize().height));

	CameraTrackingData trackingData = CameraTrackingData(Mouse::getInstance(), Vec2(416.0f, 234.0f), CameraTrackingData::CameraScrollType::Ellipse);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	// Because the mouse is a HUD object (and thus unaffected by the camera position), we need a custom function for getting the position to help with camera tracking
	trackingData.customPositionFunction = [=]()
	{
		return Mouse::getInstance()->getPosition() + GameCamera::getInstance()->getCameraPosition() - visibleSize / 2.0f;
	};

	Vec2 startPosition = this->voidCrystalNode->getPosition();

	this->lightning1->playAnimations();
	this->lightning2->playAnimations();
	this->lightning3->playAnimations();
	this->lightning4->playAnimations();
	this->lightning5->playAnimations();
	this->lightning6->playAnimations();
	this->lightning7->playAnimations();
	this->lightning8->playAnimations();
	this->lightning9->playAnimations();
	this->lightning10->playAnimations();

	this->voidCrystalNode->runAction(RepeatForever::create(Sequence::create(
		EaseSineInOut::create(MoveTo::create(4.0f, startPosition + Vec2(0.0f, -32.0f))),
		EaseSineInOut::create(MoveTo::create(4.0f, startPosition)),
		nullptr
	)));

	SoundManager::playMusicResource(MusicResources::Little_Wings_cut);

	GameCamera::getInstance()->setTarget(trackingData);
}

void WorldMap::initializePositions()
{
	super::initializePositions();

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
	super::initializeListeners();

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
