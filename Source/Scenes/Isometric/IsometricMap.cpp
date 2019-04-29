#include "IsometricMap.h"

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

IsometricMap* IsometricMap::instance = nullptr;

void IsometricMap::registerGlobalScene()
{
	if (IsometricMap::instance == nullptr)
	{
		IsometricMap::instance = new IsometricMap();
		IsometricMap::instance->autorelease();
		IsometricMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(IsometricMap::instance);
}

IsometricMap::IsometricMap()
{
}

IsometricMap::~IsometricMap()
{
}

void IsometricMap::onEnter()
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

void IsometricMap::initializePositions()
{
	super::initializePositions();
}

void IsometricMap::initializeListeners()
{
	super::initializeListeners();

	IsometricMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateMap, [](EventCustom* args)
	{
		NavigationEvents::NavigateMapArgs* mapArgs = static_cast<NavigationEvents::NavigateMapArgs*>(args->getUserData());

		if (mapArgs != nullptr && mapArgs->levelMap->isIsometric())
		{
			IsometricMap::instance->loadMap(mapArgs->levelMap);
			GlobalDirector::loadScene(IsometricMap::instance);
		}
	}));
}

void IsometricMap::loadMap(SerializableMap* levelMap)
{
	super::loadMap(levelMap);
}
