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
#include "Scenes/Platformer/Level/Combat/ChoicesMenu.h"
#include "Scenes/Platformer/Level/Combat/DefeatMenu.h"
#include "Scenes/Platformer/Level/Combat/EnemyAIHelper.h"
#include "Scenes/Platformer/Level/Combat/RewardsMenu.h"
#include "Scenes/Platformer/Level/Combat/TargetSelectionMenu.h"
#include "Scenes/Platformer/Level/Combat/TextOverlays.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/CombatHud.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Save/SaveKeys.h"

using namespace cocos2d;

const std::string CombatMap::MapKeyPropertyDisableHackerMode = "hacker-mode-disabled";

CombatMap* CombatMap::create(std::string levelFile, std::vector<std::string> mapArgs, bool playerFirstStrike,
		std::string enemyIdentifier, std::vector<std::string> playerTypes, std::vector<std::string> enemyTypes)
{
	CombatMap* instance = new CombatMap(levelFile, mapArgs, playerFirstStrike, enemyIdentifier, playerTypes, enemyTypes);

	instance->autorelease();

	return instance;
}

CombatMap::CombatMap(std::string levelFile, std::vector<std::string> mapArgs, bool playerFirstStrike,
		std::string enemyIdentifier, std::vector<std::string> playerTypes, std::vector<std::string> enemyTypes) : super(true)
{
	if (!MapBase::init())
	{
		throw std::uncaught_exception();
	}

	this->enemyIdentifier = enemyIdentifier;
	this->combatHud = CombatHud::create();
	this->choicesMenu = ChoicesMenu::create();
	this->targetSelectionMenu = TargetSelectionMenu::create();
	this->textOverlays = TextOverlays::create();
	this->timeline = Timeline::create();
	this->defeatMenu = DefeatMenu::create();
	this->rewardsMenu = RewardsMenu::create();
	this->enemyAIHelper = EnemyAIHelper::create();

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

	this->loadMap(levelFile, mapArgs);
	this->setEntityKeys(playerTypes, enemyTypes);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	MapBase::onEnter();

	this->spawnEntities();
}

void CombatMap::initializePositions()
{
	MapBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->defeatMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->rewardsMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->choicesMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->timeline->setPosition(Vec2(visibleSize.width / 2.0f, 160.0f));
}

void CombatMap::initializeListeners()
{
	MapBase::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCombatFinished, [=](EventCustom* eventCustom)
	{
		CombatEvents::CombatFinishedArgs* args = static_cast<CombatEvents::CombatFinishedArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			if (args->playerVictory)
			{
				PlatformerEnemy::saveObjectState(this->enemyIdentifier, PlatformerEnemy::SaveKeyIsDead, Value(true));

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
			expGain += StatsTables::calculateEnemyExp(entity);
		}));

		// Temporary code to prevent progression softlock for early-access users. Arbitrarily safe to delete after 9/01/2020.
		for (auto it = this->mapArgs.begin(); it != this->mapArgs.end(); it++)
		{
			if (*it == "early-access-fix")
			{
				if (SaveManager::getProfileDataOrDefault(SaveKeys::SaveKeySquallyEqExperience, Value(0)).asInt() <= 0)
				{
					// This is to make up for some users not getting exp from the first kill in the tutorial
					expGain *= 2;
				}
			}
		}

		// Note: The entities gain EXP during the animation in this function. This is a bit janky, but it's helpful to do
		// both the gain and the animations in one step
		this->textOverlays->showExpBars(expGain);

		this->runAction(Sequence::create(
			DelayTime::create(5.0f),
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

		PlatformerMap* map = PlatformerMap::create(mapResource, { }, true);

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
}

void CombatMap::loadMap(std::string mapResource, std::vector<std::string> args)
{
	super::loadMap(mapResource, args);

	if (std::find(mapArgs.begin(), mapArgs.end(), CombatMap::MapKeyPropertyDisableHackerMode) != mapArgs.end())
	{
		this->allowHackerMode = false;
	}
}

void CombatMap::setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys)
{
	this->playerEntityKeys = playerEntityKeys;
	this->enemyEntityKeys = enemyEntityKeys;
}

void CombatMap::spawnEntities()
{
	// Deserialize all enemies
	{
		int index = 1;

		for (auto it = enemyEntityKeys.begin(); it != enemyEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(*it);
			valueMap[GameObject::MapKeyFlipX] = Value(true);

			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[=] (ObjectDeserializer::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.gameObject);

					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);

			index++;
		}
	}

	// Deserialize players team
	{
		int index = 1;

		for (auto it = playerEntityKeys.begin(); it != playerEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[GameObject::MapKeyType] = PlatformerEntityDeserializer::MapKeyTypeEntity;
			valueMap[GameObject::MapKeyName] = Value(*it);
			
			ObjectDeserializer::ObjectDeserializationRequestArgs args = ObjectDeserializer::ObjectDeserializationRequestArgs(
				valueMap,
				[=] (ObjectDeserializer::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.gameObject);
					
					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index));
				}
			);

			this->platformerEntityDeserializer->deserialize(&args);

			index++;
		}
	}

	this->combatHud->bindStatsBars();
	this->timeline->initializeTimeline(true);
}
