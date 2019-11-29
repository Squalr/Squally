#include "EdgePortal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Platformer/Interactables/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EdgePortal::MapKeyEdgePortal = "edge-portal";

EdgePortal* EdgePortal::create(ValueMap& properties)
{
	EdgePortal* instance = new EdgePortal(properties);

	instance->autorelease();

	return instance;
}

EdgePortal::EdgePortal(ValueMap& properties) : super(properties, Size(properties.at(GameObject::MapKeyWidth).asFloat(), properties.at(GameObject::MapKeyHeight).asFloat()))
{
	this->requiresInteraction = false;
}

EdgePortal::~EdgePortal()
{
}

void EdgePortal::onEnter()
{
	super::onEnter();
}

void EdgePortal::initializePositions()
{
	super::initializePositions();
}

void EdgePortal::initializeListeners()
{
	super::initializeListeners();
}
