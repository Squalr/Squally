#include "CombatMap.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Maps/SerializableObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEnemy.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Events/CombatEvents.h"
#include "Events/NavigationEvents.h"
#include "Scenes/Platformer/Level/Combat/ChoicesMenu.h"
#include "Scenes/Platformer/Level/Combat/EnemyAIHelper.h"
#include "Scenes/Platformer/Level/Combat/RewardsMenu.h"
#include "Scenes/Platformer/Level/Combat/TargetSelectionMenu.h"
#include "Scenes/Platformer/Level/Combat/TextOverlays.h"
#include "Scenes/Platformer/Level/Combat/Timeline.h"
#include "Scenes/Platformer/Level/Combat/TimelineEntry.h"
#include "Scenes/Platformer/Level/Huds/CombatHud.h"

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

CombatMap::CombatMap() : super(true)
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
	this->enemyAIHelper = EnemyAIHelper::create();

	this->addChild(this->textOverlays);
	this->addChild(this->targetSelectionMenu);
	this->addChild(this->combatHud);
	this->addChild(this->enemyAIHelper);
	this->hud->addChild(this->timeline);
	this->hud->addChild(this->choicesMenu);
	this->menuHud->addChild(this->rewardsMenu);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	MapBase::onEnter();
	
	this->rewardsMenu->setVisible(false);

	this->spawnEntities();
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

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCombat, [=](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateCombatArgs* args = static_cast<NavigationEvents::NavigateCombatArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->loadMap(args->levelFile, "");

			this->setEntityKeys(args->playerTypes, args->enemyTypes);
			this->enemyIdentifier = args->enemyIdentifier;

			GlobalDirector::loadScene(this);
		}
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventCombatFinished, [=](EventCustom* eventCustom)
	{
		PlatformerEnemy::saveObjectState(this->enemyIdentifier, PlatformerEnemy::SaveKeyIsDead, Value(true));

		this->menuBackDrop->setOpacity(196);
		this->rewardsMenu->setVisible(true);

		CombatEvents::TriggerGiveRewards();
	}));

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventReturnToMap, [=](EventCustom* eventCustom)
	{
		NavigationEvents::navigateBack();
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

			valueMap[SerializableObject::MapKeyName] = Value(*it);
			valueMap[SerializableObject::MapKeyFlipX] = Value(true);

			DeserializationEvents::ObjectDeserializationRequestArgs args = DeserializationEvents::ObjectDeserializationRequestArgs(
				PlatformerEntityDeserializer::KeyTypeEntity,
				valueMap,
				[=] (DeserializationEvents::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index));
				}
			);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest(&args);

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
			
			DeserializationEvents::ObjectDeserializationRequestArgs args = DeserializationEvents::ObjectDeserializationRequestArgs(
				PlatformerEntityDeserializer::KeyTypeEntity,
				valueMap,
				[=] (DeserializationEvents::ObjectDeserializationArgs args)
				{
					PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

					CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index));
				}
			);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest(&args);

			index++;
		}
	}

	this->combatHud->bindStatsBars();
	this->timeline->initializeTimeline(true);
}
