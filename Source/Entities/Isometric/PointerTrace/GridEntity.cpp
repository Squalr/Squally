#include "GridEntity.h"

#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/NavigationEvents.h"
#include "Events/PointerTraceEvents.h"

#include "Resources/IsometricEntityResources.h"

using namespace cocos2d;

GridEntity::GridEntity(cocos2d::ValueMap& initProperties,
		std::string scmlResource,
		float scale,
		cocos2d::Vec2 offset,
		cocos2d::Size size) : super(initProperties, scmlResource, scale, offset, size)
{
	this->gridIndex = 0;
	this->movementLocked = false;
	this->movementInterrupted = false;
}

GridEntity::~GridEntity()
{
}

void GridEntity::onEnter()
{
	super::onEnter();
}

void GridEntity::initializePositions()
{
	super::initializePositions();
}

void GridEntity::interruptMovement()
{
	this->movementInterrupted = true;
}

void GridEntity::uninterruptMovement()
{
	this->movementInterrupted = false;
}

bool GridEntity::isMovementInterrupted()
{
	return this->movementInterrupted;
}

void GridEntity::lockMovement()
{
	this->movementLocked = true;
}

void GridEntity::unlockMovement()
{
	this->movementLocked = false;
}

bool GridEntity::isMovementLocked()
{
	return this->movementLocked;
}

int GridEntity::getGridIndex()
{
	return this->gridIndex;
}

void GridEntity::setGridIndex(int gridIndex)
{
	this->gridIndex = gridIndex;
}

void GridEntity::moveLeft(float speed)
{
	this->movementInterrupted = false;

	PointerTraceEvents::TriggerRequestMovement(PointerTraceEvents::PointerTraceRequestMovementArgs(
		this,
		PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Left,
		this->getGridIndex(),
		speed
	));
}

void GridEntity::moveRight(float speed)
{
	this->movementInterrupted = false;

	PointerTraceEvents::TriggerRequestMovement(PointerTraceEvents::PointerTraceRequestMovementArgs(
		this,
		PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Right,
		this->getGridIndex(),
		speed
	));
}

void GridEntity::moveUp(float speed)
{
	this->movementInterrupted = false;

	PointerTraceEvents::TriggerRequestMovement(PointerTraceEvents::PointerTraceRequestMovementArgs(
		this,
		PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Up,
		this->getGridIndex(),
		speed
	));
}

void GridEntity::moveDown(float speed)
{
	this->movementInterrupted = false;
	
	PointerTraceEvents::TriggerRequestMovement(PointerTraceEvents::PointerTraceRequestMovementArgs(
		this,
		PointerTraceEvents::PointerTraceRequestMovementArgs::Direction::Down,
		this->getGridIndex(),
		speed
	));
}
