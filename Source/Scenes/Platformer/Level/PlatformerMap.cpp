#include "PlatformerMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CipherEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Collectables/CollectablesMenu.h"
#include "Menus/Ingame/IngameMenu.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Map/MapMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Strings/Menus/Inventory/Inventory.h"

using namespace cocos2d;

const std::string PlatformerMap::MapArgClearSavedPosition = "ARGS_CLEAR_SAVED_POSITION";

PlatformerMap* PlatformerMap::create(std::string mapResource, std::vector<std::string> mapArgs, std::string transition)
{
	PlatformerMap* instance = new PlatformerMap(transition);

	instance->autorelease();

	if (std::find(mapArgs.begin(), mapArgs.end(), PlatformerMap::MapArgClearSavedPosition) != mapArgs.end())
	{
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionX);
		SaveManager::softDeleteProfileData(SaveKeys::SaveKeySquallyPositionY);
	}

	instance->loadMap(mapResource, mapArgs);

	return instance;
}

PlatformerMap::PlatformerMap(std::string transition) : super(true, true)
{
	if (!PlatformerMap::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->transition = transition;
	this->gameHud = GameHud::create();
	this->notificationHud = NotificationHud::create();
	this->cipher = nullptr;
	this->collectablesMenu = CollectablesMenu::create();
	this->mapMenu = MapMenu::create();
	this->partyMenu = PartyMenu::create();
	this->inventoryMenu = InventoryMenu::create();

	this->addLayerDeserializers({
			BackgroundDeserializer::create(),
			MusicDeserializer::create(),
			PhysicsDeserializer::create(),
			ObjectLayerDeserializer::create({
				{ CollisionDeserializer::MapKeyTypeCollision, CollisionDeserializer::create() },
				{ PlatformerDecorDeserializer::MapKeyTypeDecor, PlatformerDecorDeserializer::create() },
				{ PlatformerEntityDeserializer::MapKeyTypeEntity, PlatformerEntityDeserializer::create() },
				{ PlatformerObjectDeserializer::MapKeyTypeObject, PlatformerObjectDeserializer::create() },
				{ PlatformerTerrainDeserializer::MapKeyTypeTerrain, PlatformerTerrainDeserializer::create() }
			}),
			WeatherDeserializer::create()
		}
	);

	this->getPhysicsWorld()->setAutoStep(false);

	this->hackerModeVisibleHud->addChild(this->gameHud);
	this->topMenuHud->addChild(this->notificationHud);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->mapMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->inventoryMenu);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	super::onEnter();

	this->collectablesMenu->setVisible(false);
	this->mapMenu->setVisible(false);
	this->partyMenu->setVisible(false);
	this->inventoryMenu->setVisible(false);

	this->scheduleUpdate();
}

void PlatformerMap::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	PlatformerEvents::TriggerSpawnToTransitionLocation(PlatformerEvents::TransitionArgs(this->transition));
}

void PlatformerMap::onExit()
{
	// Zac: Optimization! This recurses through EVERY object in the map. Stop the call early since the map is being disposed anyways.
	// super::onExit();
}

void PlatformerMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->ingameMenu->setPosition(Vec2(72.0f, 0.0f));
}

void PlatformerMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherLoadArgs* args = static_cast<CipherEvents::CipherLoadArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(196);
			this->getCipherInstance()->setVisible(true);
			this->getCipherInstance()->openCipher(args->cipherPuzzleData);
			GameUtils::focus(this->getCipherInstance());
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherExitArgs* args = static_cast<CipherEvents::CipherExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(0);
			this->getCipherInstance()->setVisible(false);
			GameUtils::focus(this);
		}
	}));
	
	this->ingameMenu->setInventoryClickCallback([=]()
	{
		this->ingameMenu->setVisible(false);
		this->inventoryMenu->setVisible(true);
		this->inventoryMenu->open();
		GameUtils::focus(this->inventoryMenu);
	});

	this->ingameMenu->setPartyClickCallback([=]()
	{
		this->ingameMenu->setVisible(false);
		this->partyMenu->setVisible(true);
		GameUtils::focus(this->partyMenu);
	});
	
	this->ingameMenu->setMapClickCallback([=]()
	{
		this->ingameMenu->setVisible(false);
		this->mapMenu->setVisible(true);
		GameUtils::focus(this->mapMenu);
	});
	
	this->ingameMenu->setCollectablesClickCallback([=]()
	{
		this->ingameMenu->setVisible(false);
		this->collectablesMenu->setVisible(true);
		this->collectablesMenu->open();
		GameUtils::focus(this->collectablesMenu);
	});

	this->collectablesMenu->setReturnClickCallback([=]()
	{
		this->ingameMenu->setVisible(true);
		this->collectablesMenu->setVisible(false);
		GameUtils::focus(this->ingameMenu);
	});

	this->mapMenu->setReturnClickCallback([=]()
	{
		this->ingameMenu->setVisible(true);
		this->mapMenu->setVisible(false);
		GameUtils::focus(this->ingameMenu);
	});

	this->partyMenu->setReturnClickCallback([=]()
	{
		this->ingameMenu->setVisible(true);
		this->partyMenu->setVisible(false);
		GameUtils::focus(this->ingameMenu);
	});

	this->inventoryMenu->setReturnClickCallback([=]()
	{
		this->ingameMenu->setVisible(true);
		this->inventoryMenu->setVisible(false);
		GameUtils::focus(this->ingameMenu);
	});
}

void PlatformerMap::update(float dt)
{
	super::update(dt);

	// Fixed step seems to prevent some really obnoxious bugs where a poor frame-rate can cause the time delta to build up, causing objects to go flying
	this->getPhysicsWorld()->step(1.0f / 60.0f);
}

void PlatformerMap::loadMap(std::string mapResource, std::vector<std::string> args)
{
	ValueVector argsVector = ValueVector();

	for (auto it = args.begin(); it != args.end(); it++)
	{
		argsVector.push_back(Value(*it));
	}

	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeyMap, Value(mapResource) },
		{ SaveKeys::SaveKeyMapArgs, Value(argsVector) }
	});

	super::loadMap(mapResource, args);
}

Cipher* PlatformerMap::getCipherInstance()
{
	if (this->cipher == nullptr)
	{
		this->cipher = Cipher::create();
		this->menuHud->addChild(this->cipher);
	}

	return this->cipher;
}
