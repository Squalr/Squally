#include "Warp.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/PlatformerEvents.h"
#include "Objects/Platformer/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string Warp::MapKeyWarp = "warp";
const std::string Warp::MapKeyWarpFrom = "from";
const std::string Warp::MapKeyWarpTo = "to";
const std::string Warp::EventWarpToPrefix = "EVENT_WARP_TO_";

Warp* Warp::create(ValueMap& initProperties)
{
	Warp* instance = new Warp(initProperties);

	instance->autorelease();

	return instance;
}

Warp::Warp(ValueMap& initProperties) : super(initProperties, Size(initProperties.at(GameObject::MapKeyWidth).asFloat(), initProperties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->requiresInteraction = true;
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
		PlatformerEvents::TriggerWarpToLocation(PlatformerEvents::WarpArgs(this->getPosition()));
	});
}

void Warp::loadMap()
{
	this->broadcastMapEvent(Warp::EventWarpToPrefix + this->to, ValueMap());
}
