#include "PointerTraceMap.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/UI/Mouse.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Maps/SerializableTileLayer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Isometric/PointerTrace/GridEntity.h"
#include "Events/NavigationEvents.h"
#include "Events/PointerTraceEvents.h"
#include "Objects/Isometric/PointerTrace/MemoryGrid.h"

#include "Resources/IsometricObjectResources.h"

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
	this->collisionMap = std::map<int, bool>();
	this->segfaultMap = std::map<int, bool>();
	this->memoryGrid = nullptr;
}

PointerTraceMap::~PointerTraceMap()
{
}

void PointerTraceMap::onEnter()
{
	super::onEnter();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	ObjectEvents::QueryObjects(QueryObjectsArgs<MemoryGrid>([=](MemoryGrid* memoryGrid)
	{
		this->memoryGrid = memoryGrid;
	}));

	if (this->map != nullptr)
	{
		GameCamera::getInstance()->setBounds(Rect(0.0f, 0.0f, this->map->getMapSize().width, this->map->getMapSize().height));
	}

	this->buildCollisionMaps();
	this->initializeGridObjects();

	this->scheduleUpdate();
}

void PointerTraceMap::initializePositions()
{
	super::initializePositions();
}

void PointerTraceMap::initializeListeners()
{
	super::initializeListeners();

	this->addGlobalEventListener(EventListenerCustom::create(NavigationEvents::EventNavigatePointerTraceMap, [=](EventCustom* eventCustom)
	{
		NavigationEvents::NavigateMapArgs* args = static_cast<NavigationEvents::NavigateMapArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->loadMap(args->mapResource);

			GlobalDirector::loadScene(this);
		}
	}));

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventRequestMovement, [=](EventCustom* eventCustom)
	{
		PointerTraceEvents::PointerTraceRequestMovementArgs* args = static_cast<PointerTraceEvents::PointerTraceRequestMovementArgs*>(eventCustom->getUserData());

		this->moveGridEntity(args);
	}));
}

void PointerTraceMap::moveGridEntity(PointerTraceEvents::PointerTraceRequestMovementArgs* args)
{
	if (args == nullptr || args->gridEntity == nullptr || this->memoryGrid == nullptr)
	{
		return;
	}

	if (!args->gridEntity->isMovementLocked())
	{
		args->gridEntity->lockMovement();
		float speed = MathUtils::clamp(args->speed, 0.0f, 1.0f);
		Vec2 movementOffset = Vec2::ZERO;

		switch(args->direction)
		{
			default:
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Left:
			{
				movementOffset = Vec2(-128.0f, 64.0f);
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Right:
			{
				movementOffset = Vec2(128.0f, -64.0f);
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Up:
			{
				movementOffset = Vec2(128.0f, 64.0f);
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Down:
			{
				movementOffset = Vec2(-128.0f, -64.0f);
				break;
			}
		}

		// TODO: Collision detection
		GridEntity* gridEntity = args->gridEntity;

		gridEntity->runAction(
			Sequence::create(
				MoveBy::create(speed, movementOffset),
				CallFunc::create([=]()
				{
					gridEntity->unlockMovement();
				}),
				nullptr
			)
		);
	}
}

void PointerTraceMap::initializeGridObjects()
{

}

void PointerTraceMap::buildCollisionMaps()
{
	this->collisionMap.clear();
	this->segfaultMap.clear();

	if (this->map == nullptr)
	{
		return;
	}

	std::vector<SerializableTileLayer*> collisionLayers = this->map->getCollisionLayers();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (auto it = collisionLayers.begin(); it != collisionLayers.end(); it++)
	{
		std::vector<std::vector<int>> gidMap = (*it)->getGidMap();

		int width = gidMap.empty() ? 0 : gidMap[0].size();
		int y = 0;

		for (auto yIt = gidMap.begin(); yIt != gidMap.end(); y++, yIt++)
		{
			int x = 0;

			for (auto xIt = (*yIt).begin(); xIt != (*yIt).end(); x++, xIt++)
			{
				int gid = *xIt;

				if (gid == 1)
				{
					collisionMap[x + y * width] = true;
				}
				else if (gid == 2)
				{
					segfaultMap[x + y * width] = true;
				}
			}
		}
	}
}
