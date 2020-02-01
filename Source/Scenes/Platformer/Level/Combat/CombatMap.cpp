#include "CombatMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Deserializers.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Menus/Cards/CardsMenu.h"
#include "Menus/Collectables/CollectablesMenu.h"
#include "Menus/Ingame/IngameMenu.h"
#include "Menus/Inventory/InventoryMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Combat/EntityDropTableBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Stats/EnemyHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Enemies/Combat/EnemyCombatBehaviorGroup.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Friendly/Combat/FriendlyCombatBehaviorGroup.h"
#include "Scenes/Platformer/Level/Combat/CombatAIHelper.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/ChoicesMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/DefeatMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/FirstStrikeMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/RewardsMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/TargetSelectionMenu.h"
#include "Scenes/Platformer/Level/Combat/TextOverlays.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/CombatHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string CombatMap::MapPropertyPlayerFirstStrike = "player-first-strike";
const std::string CombatMap::MapPropertyEnemyFirstStrike = "enemy-first-strike";

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
	if (!super::initWithPhysics())
	{
		// throw std::uncaught_exceptions();
		return;
	}

	this->collectablesMenu = CollectablesMenu::create();
	this->cardsMenu = CardsMenu::create();
	this->partyMenu = PartyMenu::create();
	this->inventoryMenu = InventoryMenu::create();
	this->enemyIdentifier = enemyIdentifier;
	this->combatHud = CombatHud::create();
	this->choicesMenu = ChoicesMenu::create();
	this->textOverlays = TextOverlays::create();
	this->timeline = Timeline::create();
	this->targetSelectionMenu = TargetSelectionMenu::create(this->timeline);
	this->firstStrikeMenu = FirstStrikeMenu::create();
	this->defeatMenu = DefeatMenu::create();
	this->rewardsMenu = RewardsMenu::create();
	this->enemyAIHelper = CombatAIHelper::create();
	this->notificationHud = NotificationHud::create();
	this->entityFocusTakeOver = FocusTakeOver::create();
	this->focusTakeOver = FocusTakeOver::create();
	this->playerData = playerData;
	this->enemyData = enemyData;
	this->playerFirstStrike = playerFirstStrike;

	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();

	this->focusTakeOver->disableBackground();

	this->addLayerDeserializers({
			MetaLayerDeserializer::create({
				BackgroundDeserializer::create(),
				MusicDeserializer::create(),
				PhysicsDeserializer::create(),
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

	this->addChild(this->platformerEntityDeserializer);
	this->addChild(this->enemyAIHelper);
	this->hackerModeVisibleHud->addChild(this->textOverlays);
	this->hackerModeVisibleHud->addChild(this->combatHud);
	this->hud->addChild(this->targetSelectionMenu);
	this->hud->addChild(this->timeline);
	this->hud->addChild(this->choicesMenu);
	this->hud->addChild(this->entityFocusTakeOver);
	this->hud->addChild(this->focusTakeOver);
	this->menuHud->addChild(this->firstStrikeMenu);
	this->menuHud->addChild(this->defeatMenu);
	this->menuHud->addChild(this->rewardsMenu);
	this->topMenuHud->addChild(this->notificationHud);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->cardsMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->inventoryMenu);

	this->loadMap(levelFile);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	super::onEnter();

	this->collectablesMenu->setVisible(false);
	this->cardsMenu->setVisible(false);
	this->partyMenu->setVisible(false);
	this->inventoryMenu->setVisible(false);

	this->defer([=]()
	{
		this->spawnEntities();
		this->timeline->resumeTimeline();
	});

	this->scheduleUpdate();
}

void CombatMap::onExit()
{
	// Zac: Optimization! This recurses through EVERY object in the map. Stop the call early since the map is being disposed anyways.
	// Any disposing should be done in the destructor anyways, not onExit().
	// super::onExit();
}

void CombatMap::update(float dt)
{
	super::update(dt);
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

				this->runAction(Sequence::create(
					DelayTime::create(3.5f),
					CallFunc::create([=]()
					{
						CombatEvents::TriggerGiveRewards();
					}),
					nullptr
				));
			}
			else
			{
				this->menuBackDrop->setOpacity(196);
				this->defeatMenu->show();
			}
		}
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

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				{
					this->choicesMenu->setPosition(GameUtils::getScreenBounds(combatArgs->entry == nullptr ? nullptr : combatArgs->entry->getEntity()).origin + Vec2(-64.0f, 128.0f));

					this->entityFocusTakeOver->repeatFocus({ combatArgs->entry->getEntity() });
					this->focusTakeOver->focus({ this->choicesMenu, this->targetSelectionMenu, combatArgs->entry });

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				{
					std::vector<Node*> focusTargets = std::vector<Node*>();

					for (auto entity : this->timeline->getEntries())
					{
						if (combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget
							|| (!entity->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget)
							|| (entity->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget))
						{
							focusTargets.push_back(entity->getEntity());
						}
					}

					this->entityFocusTakeOver->repeatFocus({ focusTargets });
					this->focusTakeOver->focus({ this->choicesMenu, this->targetSelectionMenu, combatArgs->entry });
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					this->entityFocusTakeOver->unfocus();
					this->focusTakeOver->unfocus();

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
}

void CombatMap::spawnEntities()
{
	std::vector<PlatformerEntity*> friendlyEntities = std::vector<PlatformerEntity*>();
	std::vector<PlatformerEntity*> enemyEntities = std::vector<PlatformerEntity*>();

	// Deserialize players team
	{
		for (int index = 0; index < int(this->playerData.size()); index++)
		{
			ValueMap valueMap = ValueMap();

			if (this->playerData[index].entityType.empty())
			{
				continue;
			}

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(this->playerData[index].entityType);
			valueMap[GameObject::MapKeyAttachedBehavior] = this->playerData[index].battleBehavior;
			
			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[&] (ObjectDeserializer::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.gameObject);
					
					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index, [&]()
					{
						entity->attachBehavior(FriendlyCombatBehaviorGroup::create(entity));
						entity->setLocalZOrder(int32_t(entity->getPositionZ()));
						friendlyEntities.push_back(entity);
					}));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);
		}
	}
	
	// Deserialize all enemies
	{
		for (int index = 0; index < int(this->enemyData.size()); index++)
		{
			ValueMap valueMap = ValueMap();

			if (this->enemyData[index].entityType.empty())
			{
				continue;
			}

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(this->enemyData[index].entityType);
			valueMap[GameObject::MapKeyAttachedBehavior] = this->enemyData[index].battleBehavior;
			valueMap[GameObject::MapKeyFlipX] = Value(true);

			std::vector<std::string> behavior = StrUtils::splitOn(this->enemyData[index].battleBehavior, ", ", false);

			if (std::find(behavior.begin(), behavior.end(), CombatMap::MapPropertyEnemyFirstStrike) != behavior.end())
			{
				this->playerFirstStrike = false;
			}

			if (std::find(behavior.begin(), behavior.end(), CombatMap::MapPropertyPlayerFirstStrike) != behavior.end())
			{
				this->playerFirstStrike = true;
			}

			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[&] (ObjectDeserializer::ObjectDeserializationArgs deserializeArgs)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(deserializeArgs.gameObject);

					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index, [&]()
					{
						entity->attachBehavior(EnemyCombatBehaviorGroup::create(entity));
						entity->setLocalZOrder(int32_t(entity->getPositionZ()));

						entity->getAttachedBehavior<EntityDropTableBehavior>([=](EntityDropTableBehavior* entityDropTableBehavior)
						{
							entityDropTableBehavior->setDropTable(this->enemyData[index].dropPool);
						});

						enemyEntities.push_back(entity);
					}));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);
		}
	}

	std::vector<TimelineEntry*> friendlyEntries = this->timeline->initializeTimelineFriendly(this->playerFirstStrike, friendlyEntities);
	std::vector<TimelineEntry*> enemyEntries = this->timeline->initializeTimelineEnemies(this->playerFirstStrike, enemyEntities);

	this->firstStrikeMenu->show(this->playerFirstStrike);
	this->enemyAIHelper->initializeEntities(friendlyEntities, enemyEntities);
	this->combatHud->bindStatsBars(friendlyEntries, enemyEntries);
}
