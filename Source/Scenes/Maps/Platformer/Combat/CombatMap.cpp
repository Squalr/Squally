#include "CombatMap.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Events/CombatEvents.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Maps/Platformer/Combat/ChoicesMenu.h"
#include "Scenes/Maps/Platformer/Combat/RewardsMenu.h"
#include "Scenes/Maps/Platformer/Combat/TargetSelectionMenu.h"
#include "Scenes/Maps/Platformer/Combat/TextOverlays.h"
#include "Scenes/Maps/Platformer/Combat/Timeline.h"
#include "Scenes/Maps/Platformer/Combat/TimelineEntry.h"
#include "Scenes/Maps/Platformer/Huds/CombatHud.h"

using namespace cocos2d;

CombatMap* CombatMap::instance = nullptr;

void CombatMap::registerGlobalScene()
{
	if (CombatMap::instance == nullptr)
	{
		CombatMap::instance = new CombatMap();
		CombatMap::instance->autorelease();
		CombatMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(CombatMap::instance);
}

CombatMap::CombatMap()
{
	if (!MapBase::init())
	{
		throw std::uncaught_exception();
	}

	this->combatHud = CombatHud::create();
	this->choicesMenu = ChoicesMenu::create();
	this->targetSelectionMenu = TargetSelectionMenu::create();
	this->textOverlays = TextOverlays::create();
	this->timeline = Timeline::create();
	this->rewardsMenu = RewardsMenu::create();
	this->playerEntities = std::vector<PlatformerEntity*>();
	this->enemyEntities = std::vector<PlatformerEntity*>();

	this->addChild(this->textOverlays);
	this->addChild(this->targetSelectionMenu);
	this->addChild(this->combatHud);
	this->hud->addChild(this->timeline);
	this->hud->addChild(this->choicesMenu);
	this->hud->addChild(this->rewardsMenu);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	MapBase::onEnter();

	this->scheduleUpdate();

	this->initializeEntities();
}

void CombatMap::initializePositions()
{
	MapBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->rewardsMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->choicesMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->timeline->setPosition(Vec2(visibleSize.width / 2.0f, 160.0f));
}

void CombatMap::initializeListeners()
{
	MapBase::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCombat, [=](EventCustom* args)
	{
		NavigationEvents::NavigateCombatArgs* combatArgs = static_cast<NavigationEvents::NavigateCombatArgs*>(args->getUserData());

		if (combatArgs != nullptr)
		{
			this->loadMap(SerializableMap::deserialize(combatArgs->levelFile));
			this->setEntityKeys(combatArgs->playerTypes, combatArgs->enemyTypes);
			this->enemyIdentifier = combatArgs->enemyIdentifier;

			GlobalDirector::loadScene(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCombatFinished, [=](EventCustom* args)
	{
		PlatformerEnemy::saveObjectState(this->enemyIdentifier, PlatformerEnemy::SaveKeyIsDead, Value(true));
		CombatEvents::TriggerGiveRewards();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMap, [=](EventCustom* args)
	{
		NavigationEvents::navigateBack();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventChangeMenuState, [=](EventCustom* args)
	{
		CombatEvents::MenuStateArgs* combatArgs = static_cast<CombatEvents::MenuStateArgs*>(args->getUserData());

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

void CombatMap::update(float dt)
{
	super::update(dt);
}

void CombatMap::loadMap(SerializableMap* levelMap)
{
	super::loadMap(levelMap);
}

void CombatMap::setEntityKeys(std::vector<std::string> playerEntityKeys, std::vector<std::string> enemyEntityKeys)
{
	this->playerEntityKeys = playerEntityKeys;
	this->enemyEntityKeys = enemyEntityKeys;
}

void CombatMap::initializeEntities()
{
	this->playerEntities.clear();
	this->enemyEntities.clear();

	// Deserialize all enemies
	{
		int index = 1;

		for (auto it = enemyEntityKeys.begin(); it != enemyEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[SerializableObject::MapKeyName] = Value(*it);
			valueMap[SerializableObject::MapKeyFlipX] = Value(true);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest({
					PlatformerEntityDeserializer::KeyTypeEntity,
					valueMap,
					[=] (DeserializationEvents::ObjectDeserializationArgs args)
			{
				PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

				this->enemyEntities.push_back(entity);

				CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index));
			}});

			index++;
		}
	}

	// Deserialize players team
	{
		int index = 1;

		for (auto it = playerEntityKeys.begin(); it != playerEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[SerializableObject::MapKeyName] = Value(*it);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest({
					PlatformerEntityDeserializer::KeyTypeEntity,
					valueMap,
					[=] (DeserializationEvents::ObjectDeserializationArgs args)
			{
				PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

				this->playerEntities.push_back(entity);

				CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index));
			}});

			index++;
		}
	}

	this->combatHud->bindStatsBars(this->playerEntities, this->enemyEntities);
	this->targetSelectionMenu->initializeEntities(this->playerEntities, this->enemyEntities);
	this->timeline->initializeTimeline(this->playerEntities, this->enemyEntities, true);
}
