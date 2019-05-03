#include "PointerTraceMap.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/physics/CCPhysicsWorld.h"

#include "Engine/Camera/GameCamera.h"
#include "Engine/GlobalDirector.h"
#include "Engine/Maps/SerializableMap.h"
#include "Engine/Maps/SerializableTileLayer.h"
#include "Engine/Events/ObjectEvents.h"
#include "Engine/UI/HUD/Hud.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Entities/Isometric/PointerTrace/GridEntity.h"
#include "Events/NavigationEvents.h"
#include "Events/PointerTraceEvents.h"
#include "Objects/Isometric/PointerTrace/GridObject.h"
#include "Objects/Isometric/PointerTrace/MemoryGrid.h"
#include "Scenes/PointerTrace/Menus/SegfaultMenu.h"
#include "Scenes/PointerTrace/Menus/VictoryMenu.h"

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
	this->collisionDebugNode = Node::create();
	this->segfaultMenu = SegfaultMenu::create();
	this->victoryMenu = VictoryMenu::create();

	this->collisionDebugNode->setVisible(false);

	this->addChild(this->collisionDebugNode);
	this->menuHud->addChild(this->segfaultMenu);
	this->menuHud->addChild(this->victoryMenu);
}

PointerTraceMap::~PointerTraceMap()
{
}

void PointerTraceMap::onEnter()
{
	super::onEnter();

	this->segfaultMenu->setVisible(false);
	this->victoryMenu->setVisible(false);

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
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->segfaultMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
	this->victoryMenu->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));
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

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventVictory, [=](EventCustom* eventCustom)
	{
		this->openVictoryMenu();
	}));

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventRequestMovement, [=](EventCustom* eventCustom)
	{
		PointerTraceEvents::PointerTraceRequestMovementArgs* args = static_cast<PointerTraceEvents::PointerTraceRequestMovementArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->moveGridEntity(*args);
		}
	}));

	this->addEventListener(EventListenerCustom::create(PointerTraceEvents::EventResumeMovement, [=](EventCustom* eventCustom)
	{
		PointerTraceEvents::PointerTraceRequestMovementArgs* args = static_cast<PointerTraceEvents::PointerTraceRequestMovementArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->tryResumeMovement(*args);
		}
	}));
}

void PointerTraceMap::update(float dt)
{
	super::update(dt);
}

void PointerTraceMap::onDeveloperModeEnable()
{
	super::onDeveloperModeEnable();

	this->collisionDebugNode->setVisible(true);
}

void PointerTraceMap::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	this->collisionDebugNode->setVisible(false);
}

void PointerTraceMap::loadMap(std::string mapResource)
{
	super::loadMap(mapResource);

	this->segfaultMenu->setMapResource(mapResource);
}

void PointerTraceMap::tryResumeMovement(PointerTraceEvents::PointerTraceRequestMovementArgs args)
{
	if (args.gridEntity == nullptr || this->memoryGrid == nullptr)
	{
		return;
	}

	int sourceIndex = args.gridEntity->getGridIndex();

	if (this->collisionMap.find(sourceIndex) != this->collisionMap.end() || this->segfaultMap.find(sourceIndex) != this->segfaultMap.end())
	{
		args.gridEntity->lockMovement();
		this->openSegfaultMenu();
		return;
	}

	args.gridEntity->unlockMovement();
	args.gridEntity->uninterruptMovement();
	
	this->moveGridEntity(args);
}

void PointerTraceMap::moveGridEntity(PointerTraceEvents::PointerTraceRequestMovementArgs args)
{
	if (args.gridEntity == nullptr || this->memoryGrid == nullptr)
	{
		return;
	}

	if (!args.gridEntity->isMovementLocked())
	{
		float speed = MathUtils::clamp(args.speed, 0.0f, 1.0f);
		int gridWidth = this->memoryGrid->getGridWidth();
		int gridHeight = this->memoryGrid->getGridHeight();
		int sourceIndex = args.gridEntity->getGridIndex();
		int destinationIndex = sourceIndex;
		bool outOfBounds = false;
		Vec2 outOfBoundsMovement = Vec2::ZERO;

		if (gridWidth == 0 || gridHeight == 0)
		{
			return;
		}

		switch(args.direction)
		{
			default:
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Left:
			{
				destinationIndex--;
				outOfBoundsMovement = Vec2(-128.0f, -64.0f);

				if (destinationIndex / gridWidth != sourceIndex / gridWidth)
				{
					outOfBounds = true;
				}
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Right:
			{
				destinationIndex++;
				outOfBoundsMovement = Vec2(128.0f, 64.0f);
				
				if (destinationIndex / gridWidth != sourceIndex / gridWidth)
				{
					outOfBounds = true;
				}
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Up:
			{
				destinationIndex -= this->memoryGrid->getGridWidth();
				outOfBoundsMovement = Vec2(-128.0f, 64.0f);

				if (destinationIndex < 0)
				{
					outOfBounds = true;
				}
				break;
			}
			case PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Down:
			{
				destinationIndex += this->memoryGrid->getGridWidth();
				outOfBoundsMovement = Vec2(128.0f, -64.0f);

				if (destinationIndex >= this->memoryGrid->getMaxIndex())
				{
					outOfBounds = true;
				}
				
				break;
			}
		}

		// Segfault!
		if (outOfBounds || this->segfaultMap.find(destinationIndex) != this->segfaultMap.end())
		{
			args.gridEntity->lockMovement();

			args.gridEntity->runAction(
				Sequence::create(
					MoveBy::create(speed, outOfBoundsMovement),
					CallFunc::create([=]()
					{
						this->openSegfaultMenu();
					}),
					nullptr
				)
			);
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
		Vec2 destination = this->memoryGrid->gridIndexToWorldPosition(destinationIndex);
		args.gridEntity->lockMovement();

		PointerTraceEvents::PointerTraceRequestMovementArgs argsClone = PointerTraceEvents::PointerTraceRequestMovementArgs(
			args.gridEntity,
			args.direction,
			args.source,
			args.speed
		);

		args.gridEntity->runAction(
			Sequence::create(
				MoveTo::create(speed, destination),
				CallFunc::create([=]()
				{
					argsClone.gridEntity->setGridIndex(destinationIndex);
					argsClone.gridEntity->unlockMovement();

					PointerTraceEvents::TriggerEntityMoved(PointerTraceEvents::PointerTraceEntityMovedArgs(
						this->memoryGrid,
						argsClone.gridEntity,
						argsClone
					));

					if (!argsClone.gridEntity->isMovementInterrupted())
					{
						this->moveGridEntity(argsClone);
					}
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
		int y = 0;

		for (auto yIt = gidMap.begin(); yIt != gidMap.end(); y++, yIt++)
		{
			int x = 0;

			for (auto xIt = (*yIt).begin(); xIt != (*yIt).end(); x++, xIt++)
			{
				int gid = *xIt;

				// Janky garbage math. Seems to work, whatever
				float newX = float(width - y) * 128.0f;
				float newY = float(x) * 128.0f;
				float realX = (newX + newY);
				float realY = (newX - newY) / 2.0f + this->memoryGrid->getPositionY() - 320.0f;
				int gridIndex = this->memoryGrid->worldCoordsToGridIndex(Vec2(realX, realY));

				switch(gid)
				{
					case 1:
					{
						Sprite* debugBox = Sprite::create(IsometricObjectResources::PointerTrace_Selector);

						debugBox->setPosition(this->memoryGrid->gridIndexToWorldPosition(gridIndex));

						this->collisionDebugNode->addChild(debugBox);

						collisionMap.insert(gridIndex);
						break;
					}
					case 2:
					{
						Sprite* debugBox = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Selector);

						debugBox->setPosition(this->memoryGrid->gridIndexToWorldPosition(gridIndex));

						this->collisionDebugNode->addChild(debugBox);

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

void PointerTraceMap::openSegfaultMenu()
{
	this->segfaultMenu->setVisible(true);
	this->menuBackDrop->setOpacity(196);

	GameUtils::focus(this->segfaultMenu);
}

void PointerTraceMap::openVictoryMenu()
{
	this->victoryMenu->setVisible(true);
	this->menuBackDrop->setOpacity(196);

	GameUtils::focus(this->victoryMenu);
}
