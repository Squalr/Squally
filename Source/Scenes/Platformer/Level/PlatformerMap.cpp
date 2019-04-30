#include "PlatformerMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CipherEvents.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Platformer/Level/Huds/Components/CurrencyDisplay.h"
#include "Scenes/Platformer/Level/Huds/Components/RuneBar.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"

using namespace cocos2d;

PlatformerMap* PlatformerMap::instance = nullptr;

void PlatformerMap::registerGlobalScene()
{
	if (PlatformerMap::instance == nullptr)
	{
		PlatformerMap::instance = new PlatformerMap();
		PlatformerMap::instance->autorelease();
		PlatformerMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PlatformerMap::instance);
}

PlatformerMap::PlatformerMap() : super(true)
{
	if (!PlatformerMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->gameHud = GameHud::create();
	this->cipher = Cipher::create();

	this->getPhysicsWorld()->setAutoStep(false);

	this->hud->addChild(this->gameHud);
	this->menuHud->addChild(this->cipher);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	super::onEnter();

	ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
	{
		this->gameHud->getCurrencyDisplay()->setCurrencyInventory(squally->getCurrencyInventory());
		this->gameHud->getRuneBar()->setStatsTarget(squally);
		this->gameHud->getStatsBars()->setStatsTarget(squally);

		CameraTrackingData trackingData = CameraTrackingData(squally, Vec2(128.0f, 96.0f));
		GameCamera::getInstance()->setTarget(trackingData);
	}));

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));

	this->scheduleUpdate();
}

void PlatformerMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void PlatformerMap::initializeListeners()
{
	super::initializeListeners();

	PlatformerMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateMap, [](EventCustom* args)
	{
		NavigationEvents::NavigateMapArgs* mapArgs = static_cast<NavigationEvents::NavigateMapArgs*>(args->getUserData());

		if (mapArgs != nullptr && !mapArgs->levelMap->isIsometric())
		{
			PlatformerMap::instance->loadMap(mapArgs->levelMap);
			GlobalDirector::loadScene(PlatformerMap::instance);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherLoadArgs* args = static_cast<CipherEvents::CipherLoadArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(196);
			this->cipher->setVisible(true);
			this->cipher->openCipher(args->cipherPuzzleData);
			GameUtils::focus(this->cipher);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherExitArgs* args = static_cast<CipherEvents::CipherExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(0);
			this->cipher->setVisible(false);
			GameUtils::focus(this);
		}
	}));
}

void PlatformerMap::update(float dt)
{
	super::update(dt);

	// Fixed step seems to prevent some really obnoxious bugs where a poor frame-rate can cause the time delta to build up, causing objects to go flying
	this->getPhysicsWorld()->step(1.0f / 60.0f);
}

void PlatformerMap::loadMap(SerializableMap* levelMap)
{
	super::loadMap(levelMap);
}
