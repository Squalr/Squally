#include "EdgePortal.h"

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCValue.h"

#include "Engine/Events/NavigationEvents.h"
#include "Engine/Physics/CollisionObject.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/StrUtils.h"
#include "Objects/Platformer/Doors/Portal.h"
#include "Scenes/Platformer/Level/PlatformerMap.h"
#include "Scenes/Platformer/Level/Physics/PlatformerCollisionType.h"

#include "Resources/UIResources.h"

using namespace cocos2d;

const std::string EdgePortal::MapKeyEdgePortal = "edge-portal";

EdgePortal* EdgePortal::create(ValueMap& initProperties)
{
	EdgePortal* instance = new EdgePortal(initProperties);

	instance->autorelease();

	return instance;
}

EdgePortal::EdgePortal(ValueMap& initProperties) : super(initProperties, Size(initProperties.at(GameObject::MapKeyWidth).asFloat(), initProperties.at(GameObject::MapKeyHeight).asFloat()))
{
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
