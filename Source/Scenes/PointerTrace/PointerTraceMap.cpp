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
#include "Objects/Isometric/PointerTrace/GridObject.h"
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
	this->collisionMap = std::set<int>();
	this->segfaultMap = std::set<int>();
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
		float speed = MathUtils::clamp(args->speed, 0.0f, 1.0f);
		int sourceIndex = args->gridEntity->getGridIndex();
		int destinationIndex = sourceIndex;

		switch(args->direction)
		{
			default:
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Left:
			{
				destinationIndex--;
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Right:
			{
				destinationIndex++;
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Up:
			{
				destinationIndex -= this->memoryGrid->getGridWidth();
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Down:
			{
				destinationIndex += this->memoryGrid->getGridWidth();
				break;
			}
		}

		// Segfault detection (on source, not dest)
		if (this->collisionMap.find(sourceIndex) != this->collisionMap.end())
		{
			return;
		}

		// Collision detection
		if (this->collisionMap.find(destinationIndex) != this->collisionMap.end())
		{
			return;
		}

		// Out of bounds detection
		if (destinationIndex < 0 || destinationIndex > this->memoryGrid->getMaxIndex())
		{
			return;
		}

		// Create a copy or the lambda will botch this variable
		GridEntity* gridEntity = args->gridEntity;
		Vec2 destination = this->memoryGrid->gridIndexToWorldPosition(destinationIndex);
		gridEntity->lockMovement();

		gridEntity->runAction(
			Sequence::create(
				MoveTo::create(speed, destination),
				CallFunc::create([=]()
				{
					gridEntity->setGridIndex(destinationIndex);
					gridEntity->unlockMovement();
				}),
				nullptr
			)
		);
	}
}

void PointerTraceMap::initializeGridObjects()
{
	if (this->memoryGrid == nullptr)
	{
		return;
	}

	ObjectEvents::QueryObjects(QueryObjectsArgs<GridObject>([=](GridObject* gridObject)
	{
		int gridIndex = this->memoryGrid->worldCoordsToGridIndex(gridObject->getPosition());
		Vec2 realignedPosition = this->memoryGrid->gridIndexToWorldPosition(gridIndex);
		
		gridObject->setPosition(realignedPosition);
		gridObject->setGridIndex(gridIndex);
	}));

	ObjectEvents::QueryObjects(QueryObjectsArgs<GridEntity>([=](GridEntity* gridEntity)
	{
		int gridIndex = this->memoryGrid->worldCoordsToGridIndex(gridEntity->getPosition());
		Vec2 realignedPosition = this->memoryGrid->gridIndexToWorldPosition(gridIndex);
		
		gridEntity->setPosition(realignedPosition);
		gridEntity->setGridIndex(gridIndex);
	}));
}

void PointerTraceMap::buildCollisionMaps()
{
	this->collisionMap.clear();
	this->segfaultMap.clear();

	if (this->map == nullptr || this->memoryGrid == nullptr)
	{
		return;
	}

	std::vector<SerializableTileLayer*> collisionLayers = this->map->getCollisionLayers();
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (auto it = collisionLayers.begin(); it != collisionLayers.end(); it++)
	{
		std::vector<std::vector<int>> gidMap = (*it)->getGidMap();

		int width = gidMap.empty() ? 0 : gidMap[0].size();
		int height = gidMap.size();
		int xOffset = (width - this->memoryGrid->getGridWidth()) / 2;
		int yOffset = (height - this->memoryGrid->getGridHeight()) / 2;
		int y = 0;

		for (auto yIt = gidMap.begin(); yIt != gidMap.end(); y++, yIt++)
		{
			int x = 0;

			for (auto xIt = (*yIt).begin(); xIt != (*yIt).end(); x++, xIt++)
			{
				int gid = *xIt;
				int gridIndex = (x - xOffset) + (y - yOffset) * this->memoryGrid->getGridWidth();

				switch(gid)
				{
					case 1:
					{
						collisionMap.insert(gridIndex);
						break;
					}
					case 2:
					{
						segfaultMap.insert(gridIndex);
						break;
					}
					default:
					{
						break;
					}
				}
			}
		}
	}
}
