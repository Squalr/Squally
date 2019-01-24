#include "CombatMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Maps/SerializableObject.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Entities/Platformer/PlatformerEntityDeserializer.h"
#include "Events/CombatEvents.h"
#include "Events/NavigationEvents.h"

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
	if (!MapBase::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));
	this->getPhysicsWorld()->setAutoStep(false);
}

CombatMap::~CombatMap()
{
}

void CombatMap::onEnter()
{
	MapBase::onEnter();

	this->scheduleUpdate();

	this->loadEntitiesFromKeys();
}

void CombatMap::initializePositions()
{
	MapBase::initializePositions();
}

void CombatMap::initializeListeners()
{
	MapBase::initializeListeners();

	CombatMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateCombat, [](EventCustom* args)
	{
		NavigationEvents::NavigateCombatArgs* combatArgs = static_cast<NavigationEvents::NavigateCombatArgs*>(args->getUserData());

		if (combatArgs != nullptr)
		{
			CombatMap::instance->setEntityKeys(combatArgs->playerTypes, combatArgs->enemyTypes);
			CombatMap::instance->loadMap(SerializableMap::deserialize(combatArgs->levelFile));

			GlobalDirector::loadScene(CombatMap::instance);
		}
	}));
}

void CombatMap::update(float dt)
{
	super::update(dt);

	// Fixed step seems to prevent some really obnoxious bugs where a poor frame-rate can cause the time delta to build up, causing objects to go flying
	this->getPhysicsWorld()->step(1.0f / 60.0f);
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

void CombatMap::loadEntitiesFromKeys()
{
	// Deserialize all enemies
	{
		int index = 1;

		for (auto it = this->enemyEntityKeys.begin(); it != this->enemyEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[SerializableObject::MapKeyName] = Value(*it);
			valueMap[SerializableObject::MapKeyFlipX] = Value(true);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest(&DeserializationEvents::ObjectDeserializationRequestArgs(PlatformerEntityDeserializer::KeyTypeEntity, valueMap, [=](DeserializationEvents::ObjectDeserializationArgs args)
			{
				PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

				CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, true, index));
			}));

			index++;
		}
	}

	// Deserialize players team
	{
		int index = 1;

		for (auto it = this->playerEntityKeys.begin(); it != this->playerEntityKeys.end(); it++)
		{
			ValueMap valueMap = ValueMap();

			valueMap[SerializableObject::MapKeyName] = Value(*it);

			PlatformerEntityDeserializer::getInstance()->onDeserializationRequest(&DeserializationEvents::ObjectDeserializationRequestArgs(PlatformerEntityDeserializer::KeyTypeEntity, valueMap, [=](DeserializationEvents::ObjectDeserializationArgs args)
			{
				PlatformerEntity* entity = dynamic_cast<PlatformerEntity*>(args.serializableObject);

				CombatEvents::TriggerSpawn(CombatEvents::SpawnArgs(entity, false, index));
			}));

			index++;
		}
	}
}
