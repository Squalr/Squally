#include "PlatformerMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Deserializers/Deserializers.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerBannerDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CipherEvents.h"
#include "Events/HexusEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Collectables/CollectablesMenu.h"
#include "Menus/Ingame/IngameMenu.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Map/MapMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Squally/Combat/SquallyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Level/Combat/CombatMap.h"
#include "Scenes/Platformer/Level/Huds/Components/StatsBars.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/MapResources.h"

#include "Strings/Menus/Inventory/Inventory.h"

using namespace cocos2d;

PlatformerMap* PlatformerMap::create(std::string mapResource, std::string transition)
{
	PlatformerMap* instance = new PlatformerMap(transition);

	instance->autorelease();

	instance->loadMap(mapResource);

	return instance;
}

PlatformerMap::PlatformerMap(std::string transition) : super(true, true)
{
	if (!PlatformerMap::initWithPhysics())
	{
		return;
		// throw std::uncaught_exceptions();
	}

	this->transition = transition;
	this->gameHud = GameHud::create();
	this->notificationHud = NotificationHud::create();
	this->cipher = Cipher::create();
	this->hexus = Hexus::create();
	this->collectablesMenu = CollectablesMenu::create();
	this->mapMenu = MapMenu::create();
	this->partyMenu = PartyMenu::create();
	this->inventoryMenu = InventoryMenu::create();

	this->addLayerDeserializers({
			MetaLayerDeserializer::create(
			{
				BackgroundDeserializer::create(),
				MusicDeserializer::create(),
				PhysicsDeserializer::create(),
				PlatformerBannerDeserializer::create(),
			}),
			ObjectLayerDeserializer::create({
				{ CollisionDeserializer::MapKeyTypeCollision, CollisionDeserializer::create({ (PropertyDeserializer*)PlatformerAttachedBehaviorDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() }) },
				{ PlatformerDecorDeserializer::MapKeyTypeDecor, PlatformerDecorDeserializer::create() },
				{ PlatformerEntityDeserializer::MapKeyTypeEntity, PlatformerEntityDeserializer::create() },
				{ PlatformerObjectDeserializer::MapKeyTypeObject, PlatformerObjectDeserializer::create() },
				{ PlatformerTerrainDeserializer::MapKeyTypeTerrain, PlatformerTerrainDeserializer::create() },
				{ PlatformerTextureDeserializer::MapKeyTypeTexture, PlatformerTextureDeserializer::create() },
			}),
			WeatherDeserializer::create()
		}
	);

	// ZAC: Disabled for now. Auto step seems valuable actually.
	// this->getPhysicsWorld()->setAutoStep(false);

	this->hackerModeVisibleHud->addChild(this->gameHud);
	this->menuHud->addChild(this->cipher);
	this->menuHud->addChild(this->hexus);
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
	// It doesn't appear that onExit() does anything particularly vital.
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

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEngageEnemy, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::EngageEnemyArgs* args = static_cast<PlatformerEvents::EngageEnemyArgs*>(eventCustom->getUserData());

		if (args != nullptr && args->enemy != nullptr && !args->enemy->getBattleMapResource().empty())
		{
			this->engageEnemy(args->enemy, args->firstStrike);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherOpenArgs* args = static_cast<CipherEvents::CipherOpenArgs*>(eventCustom->getUserData());

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

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventOpenHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusOpenArgs* args = static_cast<HexusEvents::HexusOpenArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(196);
			this->hexus->setVisible(true);
			this->hexus->open(args->opponentData);
			
			GameUtils::focus(this->hexus);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventExitHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusExitArgs* args = static_cast<HexusEvents::HexusExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->menuBackDrop->setOpacity(0);
			this->hexus->setVisible(false);

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
	// ZAC: Nevermind. This does not seem to be an issue, and auto-step seems to make the game run much smoother in debug/slow PCs.
	// this->getPhysicsWorld()->step(1.0f / 60.0f);
}

bool PlatformerMap::loadMap(std::string mapResource)
{
	if (super::loadMap(mapResource))
	{
		SaveManager::batchSaveProfileData({
			{ SaveKeys::SaveKeyMap, Value(mapResource) },
		});

		return true;
	}

	// Error loading map! Try parsing the map to look for a reasonable fallback map
	if (StrUtils::contains(mapResource, "UnderflowRuins", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "SeaSharpCaverns", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "CastleValgrind", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "BalmerPeaks", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "DaemonsHallow", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "LambdaCrypts", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "VoidStar", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else // if (StrUtils::contains(mapResource, "EndianForest", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	
	SaveManager::batchSaveProfileData({
		{ SaveKeys::SaveKeyMap, Value(mapResource) },
	});

	return super::loadMap(mapResource);
}

void PlatformerMap::engageEnemy(PlatformerEnemy* enemy, bool firstStrike)
{
	std::vector<CombatMap::CombatData> playerCombatData = std::vector<CombatMap::CombatData>();
	std::vector<CombatMap::CombatData> enemyCombatData = std::vector<CombatMap::CombatData>();

	// Build player team
	playerCombatData.push_back(CombatMap::CombatData(Squally::MapKeySqually, SquallyCombatBehaviorGroup::MapKeyAttachedBehavior));
	
	ObjectEvents::QueryObjects<PlatformerHelper>(QueryObjectsArgs<PlatformerHelper>([&](PlatformerHelper* helper)
	{
		playerCombatData.push_back(CombatMap::CombatData(helper->getEntityKey(), helper->getBattleBehavior()));
	}), PlatformerHelper::PlatformerHelperTag);

	// Build enemy team
	enemyCombatData.push_back(CombatMap::CombatData(enemy->getEntityKey(), enemy->getBattleBehavior(), enemy->getDropPool()));

	if (!enemy->getBattleTag().empty())
	{
		ObjectEvents::QueryObjects<PlatformerEnemy>(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* enemyAlly)
		{
			if (enemyAlly != enemy)
			{
				enemyCombatData.push_back(CombatMap::CombatData(enemyAlly->getEntityKey(), enemyAlly->getBattleBehavior(), enemyAlly->getDropPool()));
			}
		}), enemy->getBattleTag());
	}

	// Start combat
	CombatMap* combatMap = CombatMap::create(
		enemy->getBattleMapResource(),
		firstStrike,
		enemy->getUniqueIdentifier(),
		playerCombatData,
		enemyCombatData
	);

	NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(combatMap));
}
