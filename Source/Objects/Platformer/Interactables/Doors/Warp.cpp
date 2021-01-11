#include "Warp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Maps/MapLayer.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Warp::MapKey = "warp";
const std::string Warp::PropertyWarpFrom = "from";
const std::string Warp::PropertyWarpTo = "to";
const std::string Warp::PropertyNoWarpCamera = "no-warp-camera";
const std::string Warp::PropertyRelayer = "relayer";
const std::string Warp::EventWarpToPrefix = "EVENT_WARP_TO_";
const float Warp::WarpCooldown = 0.5f;

Warp* Warp::create(ValueMap& properties)
{
	Warp* instance = new Warp(properties);

	instance->autorelease();

	return instance;
}

Warp::Warp(ValueMap& properties) : super(
	properties,
	Size(
		GameUtils::getKeyOrDefault(properties, GameObject::MapKeyWidth, Value(0.0f)).asFloat(),
		GameUtils::getKeyOrDefault(properties, GameObject::MapKeyHeight, Value(0.0f)).asFloat()
	),
	Vec2::ZERO,
	Color3B(16, 23, 57))
{
	this->from = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyWarpFrom, Value("")).asString();
	this->to = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyWarpTo, Value("")).asString();
	this->warpCamera = !GameUtils::getKeyOrDefault(this->properties, Warp::PropertyNoWarpCamera, Value(false)).asBool();
	this->relayer = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyRelayer, Value(false)).asBool();
	this->cooldown = 0.0f;

	this->setName("Warp from " + this->from + " to " + this->to);
	this->setInteractType(InteractType::Input);
}

Warp::~Warp()
{
}

void Warp::update(float dt)
{
	super::update(dt);

	if (this->cooldown > 0.0f)
	{
		this->disable();
		this->cooldown -= dt;

		if (this->cooldown <= 0.0f)
		{
			this->enable();
		}
	}
}

void Warp::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(Warp::EventWarpToPrefix + this->from, [=](ValueMap args)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
		{
			this->doRelayer();

			PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(squally, GameUtils::getWorldCoords3D(this), this->warpCamera));
			this->cooldown = Warp::WarpCooldown;
		}), Squally::MapKey);
	});
}

void Warp::loadMap()
{
	this->broadcastMapEvent(Warp::EventWarpToPrefix + this->to, ValueMap());

	this->cooldown = Warp::WarpCooldown;
}

void Warp::doRelayer()
{
	if (!this->relayer)
	{
		return;
	}

	MapLayer* mapLayer = GameUtils::GetFirstParentOfType<MapLayer>(this);

	if (mapLayer != nullptr)
	{
		GameUtils::changeParent(squally, mapLayer, true);
		mapLayer->setHackable();
	}
}
