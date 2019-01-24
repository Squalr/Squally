#include "CombatSpawn.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

using namespace cocos2d;

const std::string CombatSpawn::MapKeyCombatSpawn = "spawn";
const std::string CombatSpawn::MapKeySpawnType = "spawn-type";
const std::string CombatSpawn::MapKeySpawnOrder = "spawn-order";
const std::string CombatSpawn::MapKeyPlayerSpawn = "player";
const std::string CombatSpawn::MapKeyEnemySpawn = "enemy";

CombatSpawn* CombatSpawn::create(ValueMap* initProperties)
{
	CombatSpawn* instance = new CombatSpawn(initProperties);

	instance->autorelease();

	return instance;
}

CombatSpawn::CombatSpawn(ValueMap* initProperties) : SerializableObject(initProperties)
{
	this->spawnType = SpawnType::Player;
	this->spawnOrder = 1;

	if (GameUtils::keyExists(initProperties, CombatSpawn::MapKeySpawnType))
	{
		std::string spawnType = (*initProperties)[CombatSpawn::MapKeySpawnType].asString();

		if (spawnType == CombatSpawn::MapKeyEnemySpawn)
		{
			this->spawnType = SpawnType::Enemy;
		}
	}

	if (GameUtils::keyExists(initProperties, CombatSpawn::MapKeySpawnOrder))
	{
		this->spawnOrder = (*initProperties)[CombatSpawn::MapKeySpawnOrder].asInt();
	}
}

CombatSpawn::~CombatSpawn()
{
}

void CombatSpawn::onEnter()
{
	super::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(this, Vec2(0.0f, 0.0f), CameraTrackingData::CameraScrollType::Rectangle, Vec2::ZERO);
	GameCamera::getInstance()->setTarget(trackingData);
}

void CombatSpawn::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::SpawnEvent, [=](EventCustom* eventCustom)
	{
		CombatEvents::SpawnArgs* args = static_cast<CombatEvents::SpawnArgs*>(eventCustom->getUserData());

		if (args != nullptr &&
			args->spawnIndex == this->getSpawnOrder() &&
			((args->isEnemySpawn && this->getSpawnType() == SpawnType::Enemy) || (!args->isEnemySpawn && this->getSpawnType() == SpawnType::Player)) &&
			args->entity != nullptr &&
			args->entity->getParent() == nullptr)
		{
			this->addChild(args->entity);
		}
	}));
}

CombatSpawn::SpawnType CombatSpawn::getSpawnType()
{
	return this->spawnType;
}

int CombatSpawn::getSpawnOrder()
{
	return this->spawnOrder;
}
