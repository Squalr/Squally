#include "PlatformerMap.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/HUD/Hud.h"
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
}

PlatformerMap::~PlatformerMap()
{
}

void PlatformerMap::onEnter()
{
	MapBase::onEnter();

	this->scheduleUpdate();

	GameCamera::getInstance()->setScrollOffset(Vec2(64.0f, 32.0f));
	GameCamera::getInstance()->setFollowSpeed(Vec2(0.075f, 0.075f));
	GameCamera::getInstance()->setTarget(Squally::getInstance(), Vec2(0.0f, 128.0f));
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
