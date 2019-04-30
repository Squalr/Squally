#include "PointerTraceMap.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/Mouse.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Events/ObjectEvents.h"
#include "Entities/Isometric/Squally/IsometricSqually.h"
#include "Events/NavigationEvents.h"

using namespace cocos2d;

PointerTraceMap* PointerTraceMap::instance = nullptr;

void PointerTraceMap::registerGlobalScene()
{
	if (PointerTraceMap::instance == nullptr)
	{
		PointerTraceMap::instance = new PointerTraceMap();
		PointerTraceMap::instance->autorelease();
		PointerTraceMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PointerTraceMap::instance);
}

PointerTraceMap::PointerTraceMap() : super(false)
{
}

PointerTraceMap::~PointerTraceMap()
{
}

void PointerTraceMap::onEnter()
{
	super::onEnter();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ObjectEvents::QueryObjects(QueryObjectsArgs<IsometricSqually>([=](IsometricSqually* squally)
	{
		CameraTrackingData trackingData = CameraTrackingData(squally, Vec2(128.0f, 96.0f));
		GameCamera::getInstance()->setTarget(trackingData);
	}));

	GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));

	this->scheduleUpdate();
}

void PointerTraceMap::initializePositions()
{
	super::initializePositions();
}

void PointerTraceMap::initializeListeners()
{
	super::initializeListeners();

	PointerTraceMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigatePointerTraceMap, [](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateMapArgs* args = static_cast<NavigationEvents::NavigateMapArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			PointerTraceMap::instance->loadMap(args->mapResource);

			GlobalDirector::loadScene(PointerTraceMap::instance);
		}
	}));
}
