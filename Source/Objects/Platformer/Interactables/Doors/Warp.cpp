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

const std::string Warp::MapKeyWarp = "warp";
const std::string Warp::MapKeyWarpFrom = "from";
const std::string Warp::MapKeyWarpTo = "to";
const std::string Warp::EventWarpToPrefix = "EVENT_WARP_TO_";

Warp* Warp::create(ValueMap& properties)
{
	Warp* instance = new Warp(properties);

	instance->autorelease();

	return instance;
}

Warp::Warp(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->from = GameUtils::getKeyOrDefault(this->properties, Warp::MapKeyWarpFrom, Value("")).asString();
	this->to = GameUtils::getKeyOrDefault(this->properties, Warp::MapKeyWarpTo, Value("")).asString();
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
			PlatformerEvents::TriggerWarpToLocation(PlatformerEvents::WarpArgs(squally, this->getPosition()));
		}), Squally::MapKeySqually);
	});
}

void Warp::loadMap()
{
	this->broadcastMapEvent(Warp::EventWarpToPrefix + this->to, ValueMap());
}
