#include "CombatSpawn.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Utils/GameUtils.h"
#include "Entities/Platformer/PlatformerEntity.h"
#include "Events/CombatEvents.h"
#include "Scenes/Platformer/State/StateKeys.h"

using namespace cocos2d;

const std::string CombatSpawn::MapKey = "combat-spawn";
const std::string CombatSpawn::MapKeySpawnType = "spawn-type";
const std::string CombatSpawn::MapKeySpawnOrder = "spawn-order";
const std::string CombatSpawn::MapKeyPlayerSpawn = "player";
const std::string CombatSpawn::MapKeyEnemySpawn = "enemy";
const std::string CombatSpawn::PropertyZoom = "zoom";

CombatSpawn* CombatSpawn::create(ValueMap& properties)
{
	CombatSpawn* instance = new CombatSpawn(properties);

	instance->autorelease();

	return instance;
}

CombatSpawn::CombatSpawn(ValueMap& properties) : super(properties)
{
	this->spawnType = SpawnType::Player;
	this->zoom = GameUtils::getKeyOrDefault(this->properties, CombatSpawn::PropertyZoom, Value(1.0f)).asFloat();
	this->spawnOrder = GameUtils::getKeyOrDefault(this->properties, CombatSpawn::MapKeySpawnOrder, Value(0)).asInt();
	this->spawnObjectHeight = GameUtils::getKeyOrDefault(this->properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat();

	std::string spawnKey = GameUtils::getKeyOrDefault(this->properties, CombatSpawn::MapKeySpawnType, Value("")).asString();

	if (spawnKey == CombatSpawn::MapKeyEnemySpawn)
	{
		this->spawnType = SpawnType::Enemy;
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

			// Because terrain is sorted against entities, add a 1px buffer to entities to give them draw priority
			const float ZSortOffset = 1.0f;

			// Note: collision offset is factored in here because physics wont be active, thus not self-correcting.
			// Normally in the overworld, if the collision box is shifted up, gravity will sort it out after the map loads.
			// Here, there is no gravity, so the entity would appear to be loaded in a shifted up position unless we factor it in.
			Vec2 offset = Vec2(0.0f, -this->spawnObjectHeight / 2.0f + args->entity->getHoverHeight()) - args->entity->getCollisionOffset();
			GameUtils::setWorldCoords3D(args->entity, GameUtils::getWorldCoords3D(this) + Vec3(offset.x, offset.y, ZSortOffset));

			args->entity->setState(StateKeys::Zoom, Value(this->zoom), false);
			args->entity->setAnchorPoint(Vec2(0.5f, 0.0f));
			args->onSpawnSuccess();
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
