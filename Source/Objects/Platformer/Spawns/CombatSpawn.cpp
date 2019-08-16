#include "CombatSpawn.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"

using namespace cocos2d;

const std::string CombatSpawn::MapKeyCombatSpawn = "combat-spawn";
const std::string CombatSpawn::MapKeySpawnType = "spawn-type";
const std::string CombatSpawn::MapKeySpawnOrder = "spawn-order";
const std::string CombatSpawn::MapKeyPlayerSpawn = "player";
const std::string CombatSpawn::MapKeyEnemySpawn = "enemy";

CombatSpawn* CombatSpawn::create(ValueMap& properties)
{
	CombatSpawn* instance = new CombatSpawn(properties);

	instance->autorelease();

	return instance;
}

CombatSpawn::CombatSpawn(ValueMap& properties) : GameObject(properties)
{
	this->spawnType = SpawnType::Player;
	this->spawnOrder = 1;

	if (GameUtils::keyExists(properties, CombatSpawn::MapKeySpawnType))
	{
		std::string spawnType = properties[CombatSpawn::MapKeySpawnType].asString();

		if (spawnType == CombatSpawn::MapKeyEnemySpawn)
		{
			this->spawnType = SpawnType::Enemy;
		}
	}

	if (GameUtils::keyExists(properties, CombatSpawn::MapKeySpawnOrder))
	{
		this->spawnOrder = properties[CombatSpawn::MapKeySpawnOrder].asInt();
	}

	this->setAnchorPoint(Vec2(0.5f, 0.0f));
}

CombatSpawn::~CombatSpawn()
{
}

void CombatSpawn::onEnter()
{
	super::onEnter();
}

void CombatSpawn::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CombatEvents::EventSpawn, [=](EventCustom* eventCustom)
	{
		CombatEvents::SpawnArgs* args = static_cast<CombatEvents::SpawnArgs*>(eventCustom->getUserData());

		if (args != nullptr &&
			args->spawnIndex == this->getSpawnOrder() &&
			((args->isEnemySpawn && this->getSpawnType() == SpawnType::Enemy) || (!args->isEnemySpawn && this->getSpawnType() == SpawnType::Player)) &&
			args->entity != nullptr &&
			args->entity->getParent() == nullptr)
		{
			this->getParent()->addChild(args->entity);

			float height = this->properties[PlatformerEntity::MapKeyHeight].asFloat();
			args->entity->setPosition(this->getPosition() - Vec2(0.0f, height / 2.0f - args->entity->getFloatHeight()));
			args->entity->setAnchorPoint(Vec2(0.5f, 0.0f));
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
