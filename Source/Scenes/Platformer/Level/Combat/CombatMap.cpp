#include "CombatMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Deserializers.h"
#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
#include "Deserializers/Platformer/PlatformerQuestDeserializer.h"
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Maps/GameMap.h"
#include "Engine/Maps/GameObject.h"
#include "Engine/Save/SaveManager.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Helpers/EndianForest/Scrappy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Events/PlatformerEvents.h"
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
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityHealthBehavior.h"
#include "Scenes/Platformer/AttachedBehavior/Entities/Stats/EntityManaBehavior.h"
#include "Scenes/Platformer/Level/Combat/CombatAIHelper.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/CancelMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/ChoicesMenu/ChoicesMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/DefeatMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/FirstStrikeMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/RewardsMenu.h"
#include "Scenes/Platformer/Level/Combat/Menus/TargetSelectionMenu.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/CombatHud.h"
#include "Scenes/Platformer/Level/Huds/ConfirmationHud.h"
#include "Scenes/Platformer/Level/Huds/HackerModeWarningHud.h"
#include "Scenes/Platformer/Level/Huds/NotificationHud.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

#include "Resources/MapResources.h"

using namespace cocos2d;

const std::string CombatMap::PropertyPlayerFirstStrike = "player-first-strike";
const std::string CombatMap::PropertyEnemyFirstStrike = "enemy-first-strike";

CombatMap* CombatMap::create(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData)
{
	CombatMap* instance = new CombatMap(levelFile, playerFirstStrike, playerData, enemyData);

	instance->autorelease();

	return instance;
}

CombatMap::CombatMap(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData) : super(true, true)
{
	if (!super::init())
	{
		// throw std::uncaught_exceptions();
		return;
	}

	this->collectablesMenu = CollectablesMenu::create();
	this->cardsMenu = CardsMenu::create();
	this->partyMenu = PartyMenu::create();
	this->inventoryMenu = InventoryMenu::create();
	this->combatHud = CombatHud::create();
	this->timeline = Timeline::create();
	this->cancelMenu = CancelMenu::create();
	this->choicesMenu = ChoicesMenu::create(this->timeline);
	this->targetSelectionMenu = TargetSelectionMenu::create(this->timeline);
	this->firstStrikeMenu = FirstStrikeMenu::create();
	this->defeatMenu = DefeatMenu::create();
	this->rewardsMenu = RewardsMenu::create(this->timeline);
	this->enemyAIHelper = CombatAIHelper::create();
	this->hackerModeWarningHud = HackerModeWarningHud::create();
	this->notificationHud = NotificationHud::create();
	this->confirmationHud = ConfirmationHud::create();
	this->entityFocusTakeOver = FocusTakeOver::create();
	this->focusTakeOver = FocusTakeOver::create();
	this->combatEndBackdrop = Hud::create();
	this->playerData = playerData;
	this->enemyData = enemyData;
	this->playerFirstStrike = playerFirstStrike;
	this->scrappy = nullptr;

	this->platformerEntityDeserializer = PlatformerEntityDeserializer::create();

	this->focusTakeOver->setTakeOverOpacity(127);
	this->entityFocusTakeOver->setTakeOverOpacity(0);
	this->ingameMenu->disableInventory();
	this->partyMenu->disableUnstuck();

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

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->combatEndBackdrop->addChild(LayerColor::create(Color4B::BLACK, visibleSize.width, visibleSize.height));

	this->addChild(this->platformerEntityDeserializer);
	this->addChild(this->enemyAIHelper);
	this->hud->addChild(this->targetSelectionMenu);
	this->hud->addChild(this->timeline);
	this->hud->addChild(this->focusTakeOver);
	this->hud->addChild(this->choicesMenu);
	this->hud->addChild(this->cancelMenu);
	this->hackerModeVisibleHud->addChild(this->combatHud);
	this->hackerModeVisibleHud->addChild(this->entityFocusTakeOver);
	this->backMenuHud->addChild(this->hackerModeWarningHud);
	this->backMenuHud->addChild(this->firstStrikeMenu);
	this->backMenuHud->addChild(this->combatEndBackdrop);
	this->backMenuHud->addChild(this->defeatMenu);
	this->backMenuHud->addChild(this->rewardsMenu);
	this->backMenuHud->addChild(this->notificationHud);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->topMenuHud->addChild(this->cardsMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->inventoryMenu);
	this->topMenuHud->addChild(this->confirmationHud);

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
	this->combatEndBackdrop->setOpacity(0);
	
	ObjectEvents::WatchForObject<Scrappy>(this, [=](Scrappy* scrappy)
	{
		this->scrappy = scrappy;
	}, Scrappy::MapKey);

	this->defer([=]()
	{
		this->spawnEntities();
		this->timeline->resumeTimeline();
	});
}

void CombatMap::onExit()
{
	// Zac: Optimization! This recurses through EVERY object in the map. Stop the call early since the map is being disposed anyways.
	// Any disposing should be done in the destructor anyways, not onExit().
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
	this->cancelMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
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
				for (auto next : enemyData)
				{
					GameObject::saveObjectState(next.identifier, EnemyHealthBehavior::SaveKeyIsDead, Value(true));
				}

				CombatEvents::TriggerGiveExp();

				this->runAction(Sequence::create(
					DelayTime::create(2.25f),
					CallFunc::create([=]()
					{
						CombatEvents::TriggerGiveRewards();
					}),
					nullptr
				));
			}
			else
			{
				this->combatEndBackdrop->setOpacity(196);
				this->defeatMenu->show();
			}
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventGiveRewards, [=](EventCustom* eventCustom)
	{
		this->combatEndBackdrop->setOpacity(196);
		this->rewardsMenu->show();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMap, [=](EventCustom* eventCustom)
	{
		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			std::string mapResource = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();

			PlatformerMap* map = PlatformerMap::create(mapResource, { });

			return map;
		}));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMapRespawn, [=](EventCustom* eventCustom)
	{
		std::string savedMap = SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value(MapResources::EndianForest_Town_Main)).asString();

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			PlatformerEvents::TriggerBeforePlatformerMapChange();
			PlatformerMap* map = PlatformerMap::create(savedMap, PlatformerMap::TransitionRespawn);

			return map;
		}));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getUserData());

		if (combatArgs != nullptr)
		{
			switch (combatArgs->currentMenu)
			{
				case CombatEvents::MenuStateArgs::CurrentMenu::DefendSelect:
				{
					// For now, there is no defend select menu. Just wait for this state to pass.
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ActionSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::AttackSelect:
				case CombatEvents::MenuStateArgs::CurrentMenu::ItemSelect:
				{
					this->entityFocusTakeOver->unfocus();
					this->focusTakeOver->unfocus();
					
					PlatformerEntity* entity = combatArgs->entry == nullptr ? nullptr : combatArgs->entry->getEntity();
					std::vector<Node*> entityFocusTargets = std::vector<Node*>();
					std::vector<Node*> focusTargets = std::vector<Node*>();

					entityFocusTargets.push_back(entity);
					entityFocusTargets.push_back(this->scrappy);

					for (auto next : this->timeline->getEntries())
					{
						if (next->getEntity() != entity)
						{
							entityFocusTargets.push_back(next->getEntity()->getHackParticlesNode());
						}
					}

					for (auto next : this->timeline->getEntries())
					{
						focusTargets.push_back(next);
					}

					focusTargets.push_back(this->targetSelectionMenu);
					focusTargets.push_back(this->choicesMenu);
					focusTargets.push_back(this->cancelMenu);

					this->entityFocusTakeOver->positionFreezeFocus(entityFocusTargets);
					
					this->focusTakeOver->focus(focusTargets);

					for (auto entity : this->timeline->getEntries())
					{
						entity->getEntity()->getAnimations()->setOpacity(127);
					}

					if (entity != nullptr)
					{
						entity->getAnimations()->setOpacity(255);
					}

					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget:
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget:
				{
					this->entityFocusTakeOver->unfocus();
					this->focusTakeOver->unfocus();

					std::vector<Node*> entityFocusTargets = std::vector<Node*>();
					std::vector<Node*> focusTargets = std::vector<Node*>();

					for (auto entry : this->timeline->getEntries())
					{
						PlatformerEntity* entity = entry == nullptr ? nullptr : entry->getEntity();

						if (entity == nullptr)
						{
							continue;
						}

						entity->getAnimations()->setOpacity(127);

						if (combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget
							|| (!entry->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget)
							|| (entry->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget))
						{
							entity->getAnimations()->setOpacity(255);
							entityFocusTargets.push_back(entity);
						}
						else
						{
							entityFocusTargets.push_back(entity->getHackParticlesNode());
						}
					}

					std::sort(entityFocusTargets.begin(), entityFocusTargets.end(), [](Node* a, Node* b)
					{ 
						return a->getPositionZ() < b->getPositionZ();
					});

					for (auto next : this->timeline->getEntries())
					{
						focusTargets.push_back(next);
					}

					focusTargets.push_back(this->targetSelectionMenu);
					focusTargets.push_back(this->choicesMenu);
					focusTargets.push_back(this->cancelMenu);
					focusTargets.push_back(this->scrappy);

					this->entityFocusTakeOver->positionFreezeFocus({ entityFocusTargets });
					this->focusTakeOver->focus(focusTargets);
					break;
				}
				case CombatEvents::MenuStateArgs::CurrentMenu::Closed:
				{
					this->entityFocusTakeOver->unfocus();
					this->focusTakeOver->unfocus();

					this->targetSelectionMenu->selectEntity(nullptr);

					for (auto entry : this->timeline->getEntries())
					{
						PlatformerEntity* entity = entry == nullptr ? nullptr : entry->getEntity();

						if (entity == nullptr)
						{
							continue;
						}

						entity->getAnimations()->setOpacity(255);
					}

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
						friendlyEntities.push_back(entity);
					}));

					if (this->playerData[index].statsOverrides.useOverrides)
					{
						entity->getAttachedBehavior<EntityHealthBehavior>([=](EntityHealthBehavior* healthBehavior)
						{
							healthBehavior->setHealth(this->playerData[index].statsOverrides.health);
						});

						entity->getAttachedBehavior<EntityManaBehavior>([=](EntityManaBehavior* manaBehavior)
						{
							manaBehavior->setMana(this->playerData[index].statsOverrides.mana);
						});
					}
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

			if (std::find(behavior.begin(), behavior.end(), CombatMap::PropertyEnemyFirstStrike) != behavior.end())
			{
				this->playerFirstStrike = false;
			}

			if (std::find(behavior.begin(), behavior.end(), CombatMap::PropertyPlayerFirstStrike) != behavior.end())
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

	std::vector<TimelineEntry*> friendlyEntries = this->timeline->initializeTimelineFriendly(friendlyEntities);
	std::vector<TimelineEntry*> enemyEntries = this->timeline->initializeTimelineEnemies(enemyEntities);

	this->timeline->initializeStartingProgress(this->playerFirstStrike);

	this->firstStrikeMenu->show(this->playerFirstStrike);
	this->enemyAIHelper->initializeEntities(friendlyEntities, enemyEntities);
	this->combatHud->bindStatsBars(friendlyEntries, enemyEntries);
}
