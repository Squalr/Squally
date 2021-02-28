#include "CombatMap.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Deserializers/Platformer/PlatformerAttachedBehaviorDeserializer.h"
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
#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Camera/GameCamera.h"
#include "Engine/Deserializers/Meta/BackgroundDeserializer.h"
#include "Engine/Deserializers/Meta/MetaLayerDeserializer.h"
#include "Engine/Deserializers/Meta/MusicDeserializer.h"
#include "Engine/Deserializers/Meta/PhysicsDeserializer.h"
#include "Engine/Deserializers/Objects/CollisionDeserializer.h"
#include "Engine/Deserializers/Objects/ObjectLayerDeserializer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Optimization/LazyNode.h"
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
#include "Menus/Options/OptionsMenu.h"
#include "Menus/Pause/PlatformerPauseMenu.h"
#include "Menus/Party/PartyMenu.h"
#include "Menus/Pause/PauseMenu.h"
#include "Objects/Camera/CameraFocus.h"
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
#include "Scenes/Platformer/State/StateKeys.h"
#include "Scenes/Title/TitleScreen.h"

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

CombatMap::CombatMap(std::string levelFile, bool playerFirstStrike, std::vector<CombatData> playerData, std::vector<CombatData> enemyData) : super(true)
{
	this->collectablesMenu = LazyNode<CollectablesMenu>::create(CC_CALLBACK_0(CombatMap::buildCollectablesMenu, this));
	this->cardsMenu = LazyNode<CardsMenu>::create(CC_CALLBACK_0(CombatMap::buildCardsMenu, this));
	this->partyMenu = LazyNode<PartyMenu>::create(CC_CALLBACK_0(CombatMap::buildPartyMenu, this));
	this->platformerPauseMenu = LazyNode<PlatformerPauseMenu>::create(CC_CALLBACK_0(CombatMap::buildPlatformerPauseMenu, this));
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

	this->addLayerDeserializers({
			MetaLayerDeserializer::create({
				BackgroundDeserializer::create(),
				PlatformerCrackDeserializer::create(),
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
	this->topMenuHud->addChild(this->platformerPauseMenu);
	this->topMenuHud->addChild(this->partyMenu);
	this->topMenuHud->addChild(this->cardsMenu);
	this->topMenuHud->addChild(this->collectablesMenu);
	this->confirmationMenuHud->addChild(this->confirmationHud);

	this->loadMap(levelFile);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	super::onEnter();

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
		CombatEvents::CombatFinishedArgs* args = static_cast<CombatEvents::CombatFinishedArgs*>(eventCustom->getData());

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
			std::string mapResource = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyMap, Value("")).asString();

			PlatformerMap* map = PlatformerMap::create();

			map->loadMap(mapResource);

			return map;
		}));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMapRespawn, [=](EventCustom* eventCustom)
	{
		std::string savedMap = SaveManager::GetProfileDataOrDefault(SaveKeys::SaveKeyRespawnMap, Value(MapResources::EndianForest_Town_Main)).asString();

		NavigationEvents::LoadScene(NavigationEvents::LoadSceneArgs([=]()
		{
			PlatformerEvents::TriggerBeforePlatformerMapChange();
			PlatformerMap* map = PlatformerMap::create(PlatformerMap::TransitionRespawn);

			map->loadMap(savedMap);

			return map;
		}));
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* eventCustom)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(eventCustom->getData());

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
				case CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget:
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

						bool isAlive = entry->getEntity()->getRuntimeStateOrDefaultBool(StateKeys::IsAlive, true);
						bool isValidTarget = combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAnyTarget;

						isValidTarget |= (isAlive && !entry->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseAttackTarget);
						isValidTarget |= (isAlive && entry->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseBuffTarget);
						isValidTarget |= (!isAlive && entry->isPlayerEntry() && combatArgs->currentMenu == CombatEvents::MenuStateArgs::CurrentMenu::ChooseResurrectionTarget);

						if (isValidTarget)
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
}

void CombatMap::openPauseMenu(cocos2d::Node* refocusTarget)
{
	super::openPauseMenu(refocusTarget);

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

void CombatMap::onHackerModeEnable()
{
	super::onHackerModeEnable();

	ObjectEvents::QueryObjects<CameraFocus>([&](CameraFocus* cameraTarget)
	{
		GameCamera::getInstance()->setTarget(cameraTarget->getTrackingData());
	}, CameraFocus::MapKey);
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

CollectablesMenu* CombatMap::buildCollectablesMenu()
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

CardsMenu* CombatMap::buildCardsMenu()
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

PartyMenu* CombatMap::buildPartyMenu()
{
	PartyMenu* instance = PartyMenu::create();

	instance->disableUnstuck();
	instance->setReturnClickCallback([=]()
	{
		this->platformerPauseMenu->lazyGet()->setVisible(true);
		instance->setVisible(false);
		GameUtils::focus(this->platformerPauseMenu);
	});

	return instance;
}

PlatformerPauseMenu* CombatMap::buildPlatformerPauseMenu()
{
	PlatformerPauseMenu* instance = PlatformerPauseMenu::create();
	
	instance->setPosition(Vec2(72.0f, 0.0f));
	instance->disableInventory();

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
