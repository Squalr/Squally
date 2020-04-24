#include "PlatformerMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Deserializers.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerBannerDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/SceneEvents.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Input/ClickableTextNode.h"
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
#include "Menus/Ingame/IngameMenu.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Cipher/Cipher.h"
#include "Scenes/Hexus/Hexus.h"
#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHud.h"
#include "Scenes/Platformer/Level/Huds/CombatFadeInHuds/CombatFadeInHudFactory.h"
#include "Scenes/Platformer/Level/Huds/GameHud.h"
#include "Scenes/Platformer/Level/Huds/ConfirmationHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/MapResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string PlatformerMap::TransitionRespawn = "transition-special-respawn";

PlatformerMap* PlatformerMap::create(std::string mapResource, std::string transition)
{
	PlatformerMap* instance = new PlatformerMap(transition);

	instance->autorelease();

	instance->loadMap(mapResource);

	return instance;
}

PlatformerMap::PlatformerMap(std::string transition) : super(true, true)
{
	if (!PlatformerMap::init())
	{
		return;
		// throw std::uncaught_exceptions();
	}

	this->transition = transition;
	this->gameHud = GameHud::create();
	this->confirmationHud = ConfirmationHud::create();
	this->notificationHud = NotificationHud::create();
	this->combatFadeInNode = Node::create();
	this->cipher = Cipher::create();
	this->hexus = Hexus::create();
	this->collectablesMenu = CollectablesMenu::create();
	this->cardsMenu = CardsMenu::create();
	this->partyMenu = PartyMenu::create();
	this->alchemyMenu = AlchemyMenu::create();
	this->blacksmithingMenu = BlacksmithingMenu::create();
	this->inventoryMenu = InventoryMenu::create(this->partyMenu);
	this->canPause = true;
	this->awaitingConfirmationEnd = false;

	this->addLayerDeserializers({
			MetaLayerDeserializer::create(
			{
				BackgroundDeserializer::create(),
				MusicDeserializer::create(),
				PhysicsDeserializer::create(),
				PlatformerBannerDeserializer::create(),
				PlatformerRubberbandingDeserializer::create(),
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
	this->miniGameHud->addChild(this->cipher);
	this->miniGameHud->addChild(this->hexus);
	this->menuHud->addChild(this->combatFadeInNode);
	this->menuHud->addChild(this->alchemyMenu);
	this->menuHud->addChild(this->blacksmithingMenu);
	this->menuHud->addChild(this->notificationHud);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->cardsMenu);
	this->topMenuHud->addChild(this->inventoryMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->confirmationHud);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	super::onEnter();

	this->collectablesMenu->setVisible(false);
	this->cardsMenu->setVisible(false);
	this->partyMenu->setVisible(false);
	this->inventoryMenu->setVisible(false);
	this->alchemyMenu->setVisible(false);
	this->blacksmithingMenu->setVisible(false);
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

	this->ingameMenu->setPosition(Vec2(72.0f, 0.0f));
}

void PlatformerMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventEnemyEngaged, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::EnemyEngagedArgs* args = static_cast<PlatformerEvents::EnemyEngagedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			// In the future, we can pass parameters via EnemyEngagedArgs to dictate which fade-in animation to use
			this->combatFadeInNode->addChild(CombatFadeInHudFactory::getRandomFadeIn());
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventBeforeLoadRespawn, [=](EventCustom* eventCustom)
	{
		// Using combat transitions for respawn transition, for now.
		this->combatFadeInNode->addChild(CombatFadeInHudFactory::getRandomFadeIn());
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventLoadRespawn, [=](EventCustom* eventCustom)
	{
		this->combatFadeInNode->runAction(Sequence::create(
			FadeTo::create(1.0f, 0),
			CallFunc::create([=]()
			{
				this->combatFadeInNode->removeAllChildren();
			}),
			nullptr
		));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventUnstuck, [=](EventCustom* eventCustom)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			PlatformerEvents::TriggerBeforePlatformerMapChange();
			PlatformerMap* map = PlatformerMap::create(this->mapResource, this->transition);

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
		PlatformerEvents::CraftingOpenArgs* args = static_cast<PlatformerEvents::CraftingOpenArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->alchemyMenu->open(args->recipes);
			this->alchemyMenu->setVisible(true);

			GameUtils::focus(this->alchemyMenu);
			GameUtils::resume(this->notificationHud);
			GameUtils::resume(this->confirmationHud);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventOpenSmithing, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::CraftingOpenArgs* args = static_cast<PlatformerEvents::CraftingOpenArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->blacksmithingMenu->open(args->recipes);
			this->blacksmithingMenu->setVisible(true);

			GameUtils::focus(this->blacksmithingMenu);
			GameUtils::resume(this->notificationHud);
			GameUtils::resume(this->confirmationHud);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventSaveRespawn, [=](EventCustom* eventCustom)
	{
		PlatformerEvents::SaveRespawnArgs* args = static_cast<PlatformerEvents::SaveRespawnArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			SaveManager::SaveProfileData(SaveKeys::SaveKeyRespawnMap, Value(this->mapResource));
			SaveManager::SaveProfileData(SaveKeys::SaveKeyRespawnObjectId, Value(args->objectIdentifier));
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(PlatformerEvents::EventLoadRespawn, [=](EventCustom* eventCustom)
	{
		std::string savedMap = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value(MapResources::EndianForest_Town_Main)).asString();

		if (savedMap != this->mapResource)
		{
			NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
			{
				PlatformerEvents::TriggerBeforePlatformerMapChange();
				PlatformerMap* map = PlatformerMap::create(savedMap, PlatformerMap::TransitionRespawn);

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
		CipherEvents::CipherOpenArgs* args = static_cast<CipherEvents::CipherOpenArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->cipher->setVisible(true);
			this->mapNode->setVisible(false);
			this->notificationHud->setVisible(false);
			
			this->cipher->openCipher(args->cipherPuzzleData);
			GameUtils::focus(this->cipher);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventExitCipher, [=](EventCustom* eventCustom)
	{
		CipherEvents::CipherExitArgs* args = static_cast<CipherEvents::CipherExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->cipher->setVisible(false);
			this->mapNode->setVisible(true);
			this->notificationHud->setVisible(true);

			// Reinstate this if music is ever added to Cipher:
			// MusicPlayer::popMusic();
			GameUtils::focus(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventOpenHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusOpenArgs* args = static_cast<HexusEvents::HexusOpenArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->hexus->setVisible(true);
			this->hexus->open(args->opponentData);
			this->mapNode->setVisible(false);
			this->notificationHud->setVisible(false);
			
			GameUtils::focus(this->hexus);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(HexusEvents::EventExitHexus, [=](EventCustom* eventCustom)
	{
		HexusEvents::HexusExitArgs* args = static_cast<HexusEvents::HexusExitArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->hexus->setVisible(false);
			this->mapNode->setVisible(true);
			this->notificationHud->setVisible(true);
			
			GameUtils::focus(this);
		}
	}));

	this->cipher->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!this->canPause ||!GameUtils::isFocused(this->cipher))
		{
			return;
		}
		
		args->handle();

		this->openPauseMenu(this->cipher);
	});

	this->hexus->whenKeyPressed({ EventKeyboard::KeyCode::KEY_ESCAPE }, [=](InputEvents::InputArgs* args)
	{
		if (!this->canPause || !GameUtils::isFocused(this->hexus))
		{
			return;
		}
		
		args->handle();

		this->openPauseMenu(this->hexus);
	});
	
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
		this->partyMenu->open();
		GameUtils::focus(this->partyMenu);
	});
	
	this->ingameMenu->setCardsClickCallback([=]()
	{
		this->ingameMenu->setVisible(false);
		this->cardsMenu->setVisible(true);
		this->cardsMenu->open();
		GameUtils::focus(this->cardsMenu);
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

	this->cardsMenu->setReturnClickCallback([=]()
	{
		this->ingameMenu->setVisible(true);
		this->cardsMenu->setVisible(false);
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

	this->alchemyMenu->setReturnClickCallback([=]()
	{
		this->alchemyMenu->setVisible(false);
		GameUtils::focus(this);
	});

	this->blacksmithingMenu->setReturnClickCallback([=]()
	{
		this->blacksmithingMenu->setVisible(false);
		GameUtils::focus(this);
	});
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

void PlatformerMap::warpSquallyToRespawn()
{
	ObjectEvents::WatchForObject<Squally>(this, [=](Squally* squally)
	{
		std::string savedObjectId = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyRespawnObjectId, Value("error-no-object-id")).asString();

		PlatformerEvents::TriggerWarpObjectToObjectId(PlatformerEvents::WarpObjectToObjectIdArgs(squally, savedObjectId));
	}, Squally::MapKey);
}
