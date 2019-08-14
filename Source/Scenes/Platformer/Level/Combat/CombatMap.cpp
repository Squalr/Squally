#include "CombatMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Deserializers.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/StatsTables/StatsTables.h"
#include "Events/CombatEvents.h"
#include "Menus/Collectables/CollectablesMenu.h"
#include "Menus/Ingame/IngameMenu.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Map/MapMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Enemies/EnemyHealthBehavior.h"
#include "Scenes/Platformer/Level/Combat/ChoicesMenu.h"
#include "Scenes/Platformer/Level/Combat/DefeatMenu.h"
#include "Scenes/Platformer/Level/Combat/EnemyAIHelper.h"
#include "Scenes/Platformer/Level/Combat/RewardsMenu.h"
#include "Scenes/Platformer/Level/Combat/TargetSelectionMenu.h"
#include "Scenes/Platformer/Level/Combat/TextOverlays.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/CombatHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

CombatMap* CombatMap::create(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
	std::vector<CombatData> playerData, std::vector<CombatData> enemyData)
{
	CombatMap* instance = new CombatMap(levelFile, playerFirstStrike, enemyIdentifier, playerData, enemyData);

	instance->autorelease();

	return instance;
}

CombatMap::CombatMap(std::string levelFile, bool playerFirstStrike, std::string enemyIdentifier,
	std::vector<CombatData> playerData, std::vector<CombatData> enemyData) : super(true, true)
{
	if (!super::init())
	{
		throw std::uncaught_exception();
	}

	this->collectablesMenu = CollectablesMenu::create();
	this->mapMenu = MapMenu::create();
	this->partyMenu = PartyMenu::create();
	this->inventoryMenu = InventoryMenu::create();
	this->enemyIdentifier = enemyIdentifier;
	this->combatHud = CombatHud::create();
	this->choicesMenu = ChoicesMenu::create();
	this->targetSelectionMenu = TargetSelectionMenu::create();
	this->textOverlays = TextOverlays::create();
	this->timeline = Timeline::create();
	this->defeatMenu = DefeatMenu::create();
	this->rewardsMenu = RewardsMenu::create();
	this->enemyAIHelper = EnemyAIHelper::create();
	this->notificationHud = NotificationHud::create();
	this->playerData = playerData;
	this->enemyData = enemyData;

	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();

	this->addLayerDeserializers({
			BackgroundDeserializer::create(),
			MusicDeserializer::create(),
			PhysicsDeserializer::create(),
			ObjectLayerDeserializer::create({
				{ CollisionDeserializer::MapKeyTypeCollision, CollisionDeserializer::create() },
				{ PlatformerDecorDeserializer::MapKeyTypeDecor, PlatformerDecorDeserializer::create() },
				{ PlatformerEntityDeserializer::MapKeyTypeEntity, this->platformerEntityDeserializer },
				{ PlatformerObjectDeserializer::MapKeyTypeObject, PlatformerObjectDeserializer::create() },
				{ PlatformerTerrainDeserializer::MapKeyTypeTerrain, PlatformerTerrainDeserializer::create() },
			}),
			WeatherDeserializer::create()
		}
	);

	this->addChild(this->enemyAIHelper);
	this->hackerModeVisibleHud->addChild(this->textOverlays);
	this->hud->addChild(this->targetSelectionMenu);
	this->hud->addChild(this->timeline);
	this->hud->addChild(this->combatHud);
	this->hud->addChild(this->choicesMenu);
	this->menuHud->addChild(this->defeatMenu);
	this->menuHud->addChild(this->rewardsMenu);
	this->topMenuHud->addChild(this->notificationHud);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->mapMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->inventoryMenu);

	this->loadMap(levelFile, mapArgs);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	super::onEnter();

	this->collectablesMenu->setVisible(false);
	this->mapMenu->setVisible(false);
	this->partyMenu->setVisible(false);
	this->inventoryMenu->setVisible(false);

	this->spawnEntities();
}

void CombatMap::onExit()
{
	// Zac: Optimization! This recurses through EVERY object in the map. Stop the call early since the map is being disposed anyways.
	// super::onExit();
}

void CombatMap::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->ingameMenu->setPosition(Vec2(72.0f, 0.0f));
	this->defeatMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->rewardsMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->choicesMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->timeline->setPosition(Vec2(visibleSize.width / 2.0f, 160.0f));
}

void CombatMap::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCombatFinished, [=](EventCustom* eventCustom)
	{
		CombatEvents::CombatFinishedArgs* args = static_cast<CombatEvents::CombatFinishedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->playerVictory)
			{
				GameObject::saveObjectState(this->enemyIdentifier, EnemyHealthBehavior::SaveKeyIsDead, Value(true));

				CombatEvents::TriggerGiveExp();
			}
			else
			{
				this->menuBackDrop->setOpacity(196);
				this->defeatMenu->show();
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveExp, [=](EventCustom* eventCustom)
	{
		int expGain = 0;

		ObjectEvents::QueryObjects(QueryObjectsArgs<PlatformerEnemy>([&](PlatformerEnemy* entity)
		{
			expGain += StatsTables::getKillExp(entity);
		}));

		int squallyEq = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEq, Value(0)).asInt();
		int squallyExp = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(0)).asInt();

		// Note: The entities gain EXP during the animation in this function. This is a bit janky, but it's helpful to do
		// both the gain and the animations in one step
		this->textOverlays->showExpBars(expGain);

		this->runAction(Sequence::create(
			DelayTime::create(3.5f),
			CallFunc::create([=]()
			{
				CombatEvents::TriggerGiveRewards();
			}),
			nullptr
		));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* eventCustom)
	{
		this->menuBackDrop->setOpacity(196);
		this->rewardsMenu->show();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMap, [=](EventCustom* eventCustom)
	{
		std::string mapResource = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();

		PlatformerMap* map = PlatformerMap::create(mapResource, { });

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs(map));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (combatArgs != nullptr && combatArgs->entry != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					this->choicesMenu->setPosition(GameUtils::getScreenBounds(combatArgs->entry->getEntity()).origin + Vec2(0.0f, 128.0f));

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					this->choicesMenu->setVisible(false);

					break;
				}
				default:
				{
					break;
				}
			}
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

void CombatMap::spawnEntities()
{
	// Deserialize all enemies
	{
		for (int index = 0; index < this->enemyData.size(); index++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(this->enemyData[index].entityType);
			valueMap[GameObject::MapKeyAttachedBehavior] = this->enemyData[index].battleBehavior;
			valueMap[GameObject::MapKeyFlipX] = Value(true);

			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[=] (ObjectDeserializer::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.gameObject);

					entity->attachBehavior(EntityCombatBehaviorGroup::create(entity));

					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);
		}
	}

	// Deserialize players team
	{
		for (int index = 0; index < this->playerData.size(); index++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(this->playerData[index].entityType);
			valueMap[GameObject::MapKeyAttachedBehavior] = this->playerData[index].battleBehavior;
			
			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[=] (ObjectDeserializer::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.gameObject);
					
					entity->attachBehavior(EntityCombatBehaviorGroup::create(entity));
					
					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);
		}
	}

	this->combatHud->bindStatsBars();
	this->timeline->initializeTimeline(true);
}
