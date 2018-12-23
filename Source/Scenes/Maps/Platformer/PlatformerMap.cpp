#include "PlatformerMap.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/GlobalDirector.h"
#include "Engine/UI/HUD/Hud.h"
#include "Events/NavigationEvents.h"
#include "Entities/Platformer/Squally/Squally.h"

PlatformerMap* PlatformerMap::instance = nullptr;

void PlatformerMap::registerGlobalScene()
{
	if (PlatformerMap::instance == nullptr)
	{
		PlatformerMap::instance = new PlatformerMap();
		PlatformerMap::instance->autorelease();
		PlatformerMap::instance->initializeListeners();
	}

	GlobalDirector::registerGlobalScene(PlatformerMap::instance);
}

PlatformerMap::PlatformerMap()
{
	if (!MapBase::initWithPhysics())
	{
		throw std::uncaught_exception();
	}

	this->getPhysicsWorld()->setGravity(Vec2(0.0f, -768.0f));
	this->getPhysicsWorld()->setAutoStep(false);
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	MapBase::onEnter();

	CameraTrackingData trackingData = CameraTrackingData(Squally::getInstance(), Vec2(128.0f, 96.0f));
	GameCamera::getInstance()->setTarget(trackingData);

	this->scheduleUpdate();
}

void PlatformerMap::initializePositions()
{
	MapBase::initializePositions();
}

void PlatformerMap::initializeListeners()
{
	MapBase::initializeListeners();

	PlatformerMap::instance->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigateMap, [](EventCustom* args)
	{
		NavigationEvents::NavigateMapArgs* mapArgs = static_cast<NavigationEvents::NavigateMapArgs*>(args->getUserData());

		if (mapArgs != nullptr)
		{
			PlatformerMap::instance->loadMap(mapArgs->levelMap);
			GlobalDirector::loadScene(PlatformerMap::instance);
		}
	}));
}

void PlatformerMap::update(float dt)
{
	MapBase::update(dt);

	// Fixed step seems to prevent some really obnoxious bugs where a poor frame-rate can cause the time delta to build up, causing objects to go flying
	this->getPhysicsWorld()->step(1.0f / 60.0f);
}
