#include "PlatformerMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCFastTMXTiledMap.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerComponentDeserializer.h"
#include "Deserializers/Platformer/PlatformerBannerDeserializer.h"
#include "Deserializers/Platformer/PlatformerCrackDeserializer.h"
#include "Deserializers/Platformer/PlatformerDecorDeserializer.h"
#include "Deserializers/Platformer/PlatformerEntityDeserializer.h"
#include "Deserializers/Platformer/PlatformerHideMiniMapDeserializer.h"
#include "Deserializers/Platformer/PlatformerMiniMapRequiredItemDeserializer.h"
#include "Deserializers/Platformer/PlatformerObjectDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Deserializers/Platformer/PlatformerRubberbandingDeserializer.h"
#include "Deserializers/Platformer/PlatformerTerrainDeserializer.h"
#include "Deserializers/Platformer/PlatformerTextureDeserializer.h"
#include "Deserializers/WeatherDeserializer.h"
#include "Engine/Deserializers/Meta/BackgroundDeserializer.h"
#include "Engine/Deserializers/Meta/MetaLayerDeserializer.h"
#include "Engine/Deserializers/Meta/MusicDeserializer.h"
#include "Engine/Deserializers/Meta/PhysicsDeserializer.h"
#include "Engine/Deserializers/Objects/CollisionDeserializer.h"
#include "Engine/Deserializers/Objects/ObjectLayerDeserializer.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Optimization/LazyNode.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Sound/MusicPlayer.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerHelper.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/CipherEvents.h"
#include "Events/HexusEvents.h"
#include "Events/NotificationEvents.h"
#include "Events/PlatformerEvents.h"
#include "Menus/Cards/CardsMenu.h"
#include "Menus/Collectables/CollectablesMenu.h"
#include "Menus/Crafting/AlchemyMenu.h"
#include "Menus/Crafting/BlacksmithingMenu.h"
#include "Menus/Crafting/DismantleMenu.h"
#include "Menus/CursorSets.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Inventory/ItemInfoMenu.h"
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PlatformerPauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Hexus/HelpMenus/HelpMenu.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Platformer/Level/Huds/FadeHuds/FadeHud.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"
#include "Scenes/Platformer/Level/Huds/ConfirmationHud.h"
#include "Scenes/Platformer/Level/Huds/MiniMap/MiniMap.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Save/SaveKeys.h"
#include "Scenes/Title/TitleScreen.h"

#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PlatformerMap::TransitionRespawn = "transition-special-respawn";

PlatformerMap* PlatformerMap::create(std::string transition)
{
	PlatformerMap* instance = new PlatformerMap(transition);

	instance->autorelease();

	return instance;
}

PlatformerMap::PlatformerMap(std::string transition) : super(true)
{
	this->transition = transition;
	this->gameHud = GameHud::create();
	this->confirmationHud = ConfirmationHud::create();
	this->notificationHud = NotificationHud::create();
	this->fadeHud = FadeHud::create();
	this->cipher = LazyNode<Cipher>::create(CC_CALLBACK_0(PlatformerMap::buildCipher, this));
	this->hexus = LazyNode<Hexus>::create(CC_CALLBACK_0(PlatformerMap::buildHexus, this));
	this->platformerPauseMenu = LazyNode<PlatformerPauseMenu>::create(CC_CALLBACK_0(PlatformerMap::buildPlatformerPauseMenu, this));
	this->cardHelpMenu = LazyNode<HelpMenu>::create(CC_CALLBACK_0(PlatformerMap::buildHexusCardHelpMenu, this));
	this->itemInfoMenu = LazyNode<ItemInfoMenu>::create(CC_CALLBACK_0(PlatformerMap::buildItemInfoMenu, this));
	this->collectablesMenu = LazyNode<CollectablesMenu>::create(CC_CALLBACK_0(PlatformerMap::buildCollectablesMenu, this));
	this->cardsMenu = LazyNode<CardsMenu>::create(CC_CALLBACK_0(PlatformerMap::buildCardsMenu, this));
	this->partyMenu = LazyNode<PartyMenu>::create(CC_CALLBACK_0(PlatformerMap::buildPartyMenu, this));
	this->alchemyMenu = LazyNode<AlchemyMenu>::create(CC_CALLBACK_0(PlatformerMap::buildAlchemyMenu, this));
	this->blacksmithingMenu = LazyNode<BlacksmithingMenu>::create(CC_CALLBACK_0(PlatformerMap::buildBlacksmithingMenu, this));
	this->dismantleMenu = LazyNode<DismantleMenu>::create(CC_CALLBACK_0(PlatformerMap::buildDismantleMenu, this));
	this->inventoryMenu = LazyNode<InventoryMenu>::create(CC_CALLBACK_0(PlatformerMap::buildInventoryMenu, this));
	this->canPause = true;
	this->awaitingConfirmationEnd = false;
	this->miniMap = MiniMap::create();

	this->addLayerDeserializers({
			MetaLayerDeserializer::create(
			{
				BackgroundDeserializer::create(),
				PlatformerCrackDeserializer::create(),
				MusicDeserializer::create(),
				PhysicsDeserializer::create(),
				PlatformerBannerDeserializer::create(),
				PlatformerRubberbandingDeserializer::create(),
				PlatformerHideMiniMapDeserializer::create(),
				PlatformerMiniMapRequiredItemDeserializer::create(),
			}),
			ObjectLayerDeserializer::create({
				{ CollisionDeserializer::MapKeyTypeCollision, CollisionDeserializer::create({ (PropertyDeserializer*)PlatformerComponentDeserializer::create(), (PropertyDeserializer*)PlatformerQuestDeserializer::create() }) },
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
	this->menuHud->addChild(this->miniMap);
	this->menuHud->addChild(this->alchemyMenu);
	this->menuHud->addChild(this->blacksmithingMenu);
	this->menuHud->addChild(this->dismantleMenu);
	this->menuHud->addChild(this->fadeHud);
	this->menuHud->addChild(this->notificationHud);
	this->miniGameHud->addChild(this->cipher);
	this->miniGameHud->addChild(this->hexus);
	this->miniGameHud->addChild(this->itemInfoMenu);
	this->miniGameHud->addChild(this->cardHelpMenu);
	this->topMenuHud->addChild(this->platformerPauseMenu);
	this->topMenuHud->addChild(this->cardsMenu);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->inventoryMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->confirmationMenuHud->addChild(this->confirmationHud);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	super::onEnter();
}

void PlatformerMap::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	PlatformerEvents::TriggerSpawnToTransitionLocation(PlatformerEvents::TransitionArgs(this->transition));

	if (this->transition == PlatformerMap::TransitionRespawn)
	{
		// Override transition spawn location if respawning
		this->warpSquallyToRespawn();
	}
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
}

void PlatformerMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEnemyEngaged, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::EnemyEngagedArgs* args = static_cast<PlatformerEvents::EnemyEngagedArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			// In the future, we can pass parameters via EnemyEngagedArgs to dictate which fade-in animation to use
			this->fadeHud->runAnim(FadeHud::FadeHudType::Triangles);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventRelocateMiniMap, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::RelocateMiniMapArgs* args = static_cast<PlatformerEvents::RelocateMiniMapArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->miniMap->setPositioning(args->miniMapPositioning);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforeLoadRespawn, [=](EventCustom* eventCustom)
	{
		// Using combat transitions for respawn transition, for now.
		this->fadeHud->runAnim(FadeHud::FadeHudType::Normal);
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventLoadRespawn, [=](EventCustom* eventCustom)
	{
		this->fadeHud->resetAnims();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventUnstuck, [=](EventCustom* eventCustom)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			PlatformerEvents::TriggerBeforePlatformerMapChange();
			PlatformerMap* map = PlatformerMap::create(this->transition);

			map->loadMap(this->mapResource);

			return map;
		}));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventConfirmation, [=](EventCustom* eventCustom)
	{
		this->awaitingConfirmationEnd = true;
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(NotificationEvents::EventConfirmationEnd, [=](EventCustom* eventCustom)
	{
		if (this->awaitingConfirmationEnd)
		{
			GameUtils::focus(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventOpenAlchemy, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::CraftingOpenArgs* args = static_cast<PlatformerEvents::CraftingOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->alchemyMenu->lazyGet()->open(args->recipes);
			this->alchemyMenu->lazyGet()->setVisible(true);

			GameUtils::focus(this->alchemyMenu);
			GameUtils::resume(this->notificationHud);
			GameUtils::resume(this->confirmationHud);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventOpenSmithing, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::CraftingOpenArgs* args = static_cast<PlatformerEvents::CraftingOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->blacksmithingMenu->lazyGet()->open(args->recipes);
			this->blacksmithingMenu->lazyGet()->setVisible(true);

			GameUtils::focus(this->blacksmithingMenu);
			GameUtils::resume(this->notificationHud);
			GameUtils::resume(this->confirmationHud);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventOpenDismantle, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::CraftingOpenArgs* args = static_cast<PlatformerEvents::CraftingOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->dismantleMenu->lazyGet()->open(args->recipes);
			this->dismantleMenu->lazyGet()->setVisible(true);

			GameUtils::focus(this->dismantleMenu);
			GameUtils::resume(this->notificationHud);
			GameUtils::resume(this->confirmationHud);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventSaveRespawn, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::SaveRespawnArgs* args = static_cast<PlatformerEvents::SaveRespawnArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			SaveManager::BatchSaveProfileData(
				{
					{ SaveKeys::SaveKeyRespawnMap, Value(this->mapResource) },
					{ SaveKeys::SaveKeyRespawnObjectId, Value(args->objectIdentifier) },
				}
			);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventLoadRespawn, [=](EventCustom* eventCustom)
	{
		std::string savedMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value(MapResources::EndianForest_Town_Main)).asString();

		if (savedMap != this->mapResource)
		{
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
			{
				PlatformerEvents::TriggerBeforePlatformerMapChange();
				PlatformerMap* map = PlatformerMap::create(PlatformerMap::TransitionRespawn);

				map->loadMap(savedMap);

				return map;
			}));
		}
		else
		{
			this->warpSquallyToRespawn();
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventOpenCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherOpenArgs* args = static_cast<CipherEvents::CipherOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->menuHud->setVisible(false);
			this->mapNode->setVisible(false);
			this->notificationHud->setVisible(false);
			this->cipher->lazyGet()->setVisible(true);
			this->cipher->lazyGet()->openCipher(args->cipherPuzzleData);

			GameUtils::focus(this->cipher);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherExitArgs* args = static_cast<CipherEvents::CipherExitArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->menuHud->setVisible(true);
			this->mapNode->setVisible(true);
			this->notificationHud->setVisible(true);
			this->cipher->lazyGet()->setVisible(false);

			// Reinstate this if music is ever added to Cipher:
			// MusicPlayer::popMusic();
			GameUtils::focus(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventOpenHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusOpenArgs* args = static_cast<HexusEvents::HexusOpenArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->menuHud->setVisible(false);
			this->mapNode->setVisible(false);
			this->notificationHud->setVisible(false);
			this->hexus->lazyGet()->open(args->opponentData);
			this->hexus->lazyGet()->setVisible(true);

			GameUtils::focus(this->hexus);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventExitHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusExitArgs* args = static_cast<HexusEvents::HexusExitArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->menuHud->setVisible(true);
			this->mapNode->setVisible(true);
			this->notificationHud->setVisible(true);
			this->hexus->lazyGet()->setVisible(false);

			GameUtils::focus(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventShowHelpMenuOutsideOfGame, [=](EventCustom* eventCustom)
	{
		HexusEvents::HelpMenuArgs* args = static_cast<HexusEvents::HelpMenuArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->cardHelpMenu->lazyGet()->openMenu(args->cardData, true, args->onExit);
			this->cardHelpMenu->lazyGet()->setVisible(true);
			
			GameUtils::focus(this->cardHelpMenu);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventOpenItemInfo, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::ItemInfoArgs* args = static_cast<PlatformerEvents::ItemInfoArgs*>(eventCustom->getData());

		if (args != nullptr)
		{
			this->buildItemInfoMenu();
			
			this->itemInfoMenu->lazyGet()->open(args->item, args->onTakeDisplayItem, args->onExit);
			this->itemInfoMenu->lazyGet()->setVisible(true);
			
			GameUtils::focus(this->itemInfoMenu);
		}
	}));
}

bool PlatformerMap::loadMapFromTmx(std::string mapResource, cocos_experimental::TMXTiledMap* mapRaw)
{
	CollisionObject::UniverseId = 0;

	if (super::loadMapFromTmx(mapResource, mapRaw))
	{
		SaveManager::BatchSaveProfileData({
			{ SaveKeys::SaveKeyMap, Value(mapResource) },
		});

		this->loadMiniMap(mapResource, mapRaw);

		return true;
	}

	// Error loading map! Try parsing the map to look for a reasonable fallback map
	if (StrUtils::contains(mapResource, "UnderflowRuins", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "DataMines", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "CastleValgrind", true))
	{
		mapResource = MapResources::EndianForest_Town_Main;
	}
	else if (StrUtils::contains(mapResource, "BallmerPeaks", true))
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
	
	SaveManager::BatchSaveProfileData({
		{ SaveKeys::SaveKeyMap, Value(mapResource) },
	});

	bool fallbackResult = super::loadMap(mapResource);

	this->loadMiniMap(mapResource, mapRaw);

	return fallbackResult;
}

void PlatformerMap::openPauseMenu(cocos2d::Node* refocusTarget)
{
	super::openPauseMenu(refocusTarget);
	
	CursorSets::SetActiveCursorSet(CursorSets::Default);

	if (!this->canPause)
	{
		return;
	}

	this->platformerPauseMenu->lazyGet()->open([=]()
	{
		this->menuBackDrop->setOpacity(0);
		GameUtils::focus(refocusTarget);
	});
}

void PlatformerMap::warpSquallyToRespawn()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		std::string savedObjectId = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnObjectId, Value("error-no-object-id")).asString();

		PlatformerEvents::TriggerWarpObjectToObjectId(PlatformerEvents::WarpObjectToObjectIdArgs(squally, savedObjectId));
	}, Squally::MapKey);
}

void PlatformerMap::loadMiniMap(std::string mapResource, cocos_experimental::TMXTiledMap* mapRaw)
{
	// Increase ref count so that it is valid when mini-map parses it later
	if (mapRaw)
	{
		mapRaw->retain();
	}

	// Data race! By defering for awhile, a very strange bug is avoided that can cause Squally to glitch out and fly away.
	// No idea how loading the mini-map interferes with this, but debugging it was becoming too big of a time sink.
	this->defer([=]()
	{
		// No need to retain/release mapRaw before passing to defer, this is permenantly cached & retained in MapBase.
		if (mapRaw)
		{
			// Best effort load. No reason it shouldn't work since the mapRaw object is deserialized.
			this->miniMap->loadMapFromTmx(mapResource, mapRaw);
			mapRaw->release();
		}
	}, 15);
}


Cipher* PlatformerMap::buildCipher()
{
	Cipher* instance = Cipher::create();

	instance->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!this->canPause ||!GameUtils::isFocused(instance))
		{
			return;
		}
		
		args->handle();

		this->openPauseMenu(instance);
	});

	return instance;
}

Hexus* PlatformerMap::buildHexus()
{
	Hexus* instance = Hexus::create();

	instance->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!this->canPause || !GameUtils::isFocused(instance))
		{
			return;
		}
		
		args->handle();

		this->openPauseMenu(instance);
	});
	
	return instance;
}

HelpMenu* PlatformerMap::buildHexusCardHelpMenu()
{
	HelpMenu* instance = HelpMenu::create();

	instance->setExitCallback([=]()
	{
		instance->setVisible(false);

		GameUtils::focus(this);
	});

	instance->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!this->canPause ||!GameUtils::isFocused(instance))
		{
			return;
		}
		
		args->handle();

		instance->setVisible(false);

		GameUtils::focus(this);
	});

	return instance;
}

CollectablesMenu* PlatformerMap::buildCollectablesMenu()
{
	CollectablesMenu* instance = CollectablesMenu::create();

	instance->setReturnClickCallback([=]()
	{
		this->platformerPauseMenu->lazyGet()->setVisible(true);
		instance->setVisible(false);
		GameUtils::focus(this->platformerPauseMenu);
	});

	return instance;
}

ItemInfoMenu* PlatformerMap::buildItemInfoMenu()
{
	ItemInfoMenu* instance = ItemInfoMenu::create();

	instance->setReturnClickCallback([=]()
	{
		instance->setVisible(false);

		GameUtils::focus(this);
	});

	instance->whenKeyPressed({ InputEvents::KeyCode::KEY_ESCAPE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		if (!this->canPause ||!GameUtils::isFocused(instance))
		{
			return;
		}
		
		args->handle();

		instance->setVisible(false);

		GameUtils::focus(this);
	});

	return instance;
}

CardsMenu* PlatformerMap::buildCardsMenu()
{
	CardsMenu* instance = CardsMenu::create();

	instance->setReturnClickCallback([=]()
	{
		this->platformerPauseMenu->lazyGet()->setVisible(true);
		instance->setVisible(false);
		GameUtils::focus(this->platformerPauseMenu);
	});

	return instance;
}

PartyMenu* PlatformerMap::buildPartyMenu()
{
	PartyMenu* instance = PartyMenu::create();

	instance->setReturnClickCallback([=]()
	{
		this->platformerPauseMenu->lazyGet()->setVisible(true);
		instance->setVisible(false);
		GameUtils::focus(this->platformerPauseMenu);
	});

	return instance;
}

InventoryMenu* PlatformerMap::buildInventoryMenu()
{
	InventoryMenu* instance = InventoryMenu::create(this->partyMenu);

	instance->setReturnClickCallback([=]()
	{
		this->platformerPauseMenu->lazyGet()->setVisible(true);
		instance->setVisible(false);
		GameUtils::focus(this->platformerPauseMenu);
	});

	return instance;
}

AlchemyMenu* PlatformerMap::buildAlchemyMenu()
{
	AlchemyMenu* instance = AlchemyMenu::create();

	instance->setReturnClickCallback([=]()
	{
		instance->setVisible(false);
		GameUtils::focus(this);
	});

	return instance;
}

BlacksmithingMenu* PlatformerMap::buildBlacksmithingMenu()
{
	BlacksmithingMenu* instance = BlacksmithingMenu::create();

	instance->setReturnClickCallback([=]()
	{
		instance->setVisible(false);
		GameUtils::focus(this);
	});
	
	return instance;
}

DismantleMenu* PlatformerMap::buildDismantleMenu()
{
	DismantleMenu* instance = DismantleMenu::create();

	instance->setReturnClickCallback([=]()
	{
		instance->setVisible(false);
		GameUtils::focus(this);
	});

	return instance;
}

PlatformerPauseMenu* PlatformerMap::buildPlatformerPauseMenu()
{
	PlatformerPauseMenu* instance = PlatformerPauseMenu::create();

	instance->setPosition(Vec2(72.0f, 0.0f));

	instance->setOptionsClickCallback([=]()
	{
		instance->setVisible(false);
		this->optionsMenu->lazyGet()->setVisible(true);
		GameUtils::focus(this->optionsMenu);
	});

	instance->setQuitToTitleClickCallback([=]()
	{
		this->menuBackDrop->setOpacity(0);
		instance->setVisible(false);
		
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]() { return TitleScreen::getInstance(); }));
	});

	instance->setInventoryClickCallback([=]()
	{
		instance->setVisible(false);
		this->inventoryMenu->lazyGet()->open();
		this->inventoryMenu->lazyGet()->setVisible(true);

		GameUtils::focus(this->inventoryMenu);
	});

	instance->setPartyClickCallback([=]()
	{
		instance->setVisible(false);
		this->partyMenu->lazyGet()->setVisible(true);
		this->partyMenu->lazyGet()->open();
		GameUtils::focus(this->partyMenu);
	});
	
	instance->setCardsClickCallback([=]()
	{
		instance->setVisible(false);
		this->cardsMenu->lazyGet()->setVisible(true);
		this->cardsMenu->lazyGet()->open();
		GameUtils::focus(this->cardsMenu);
	});
	
	instance->setCollectablesClickCallback([=]()
	{
		instance->setVisible(false);
		this->collectablesMenu->lazyGet()->setVisible(true);
		this->collectablesMenu->lazyGet()->open();
		GameUtils::focus(this->collectablesMenu);
	});

	return instance;
}
