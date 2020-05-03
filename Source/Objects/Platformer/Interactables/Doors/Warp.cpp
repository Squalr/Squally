#include "Warp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Entities/Platformer/Squally/Squally.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Warp::MapKey = "warp";
const std::string Warp::PropertyWarpFrom = "from";
const std::string Warp::PropertyWarpTo = "to";
const std::string Warp::PropertyRelayer = "relayer";
const std::string Warp::EventWarpToPrefix = "EVENT_WARP_TO_";

Warp* Warp::create(ValueMap& properties)
{
	Warp* instance = new Warp(properties);

	instance->autorelease();

	return instance;
}

Warp::Warp(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->from = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyWarpFrom, Value("")).asString();
	this->to = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyWarpTo, Value("")).asString();
	this->relayer = GameUtils::getKeyOrDefault(this->properties, Warp::PropertyRelayer, Value(false)).asBool();

	this->setInteractType(InteractType::Input);
}

Warp::~Warp()
{
}

void Warp::onEnter()
{
	super::onEnter();
}

void Warp::initializePositions()
{
	super::initializePositions();
}

void Warp::initializeListeners()
{
	super::initializeListeners();

	this->listenForMapEvent(Warp::EventWarpToPrefix + this->from, [=](ValueMap args)
	{
		ObjectEvents::QueryObjects(QueryObjectsArgs<Squally>([=](Squally* squally)
		{
			if (this->relayer)
			{
				// TODO: Relayer target object to the same layer as this warp
			}

			PlatformerEvents::TriggerWarpObjectToLocation(PlatformerEvents::WarpObjectToLocationArgs(squally, GameUtils::getWorldCoords3D(this)));
		}), Squally::MapKey);
	});
}

void Warp::loadMap()
{
	this->broadcastMapEvent(Warp::EventWarpToPrefix + this->to, ValueMap());
}
