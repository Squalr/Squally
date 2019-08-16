#include "GridEntity.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionEase.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"

#include "Engine/Animations/SmartAnimationNode.h"
#include "Engine/Input/Input.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/PointerTraceEvents.h"

#include "Resources/IsometricEntityResources.h"
#include "Resources/IsometricObjectResources.h"

using namespace cocos2d;

GridEntity::GridEntity(cocos2d::ValueMap& properties,
		std::string scmlResource,
		float scale,
		cocos2d::Vec2 offset,
		cocos2d::Size size) : super(properties, scmlResource, scale, offset, size)
{
	this->gridIndex = 0;
	this->initialGridIndex = 0;
	this->movementLocked = false;
	this->movementInterrupted = false;
	this->shadow = Sprite::create(IsometricObjectResources::PointerTrace_Crystals_Shadow);

	this->underNode->addChild(this->shadow);
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

int GridEntity::getInitialGridIndex()
{
	return this->initialGridIndex;
}

int GridEntity::getGridIndex()
{
	return this->gridIndex;
}

void GridEntity::setInitialGridIndex(int gridIndex)
{
	this->initialGridIndex = gridIndex;

	this->setGridIndex(gridIndex);
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

void GridEntity::runJumpAnimation(Vec2 destPosition, std::function<void()> callback)
{
	Vec2 startAnimPosition = this->animationNode->getPosition();
	Vec2 delta = (destPosition - startAnimPosition) - this->getPosition();
	Vec2 peakPosition = startAnimPosition + Vec2(0.0f, 2048.0f);
	Vec2 destAnimPosition = startAnimPosition + delta;
	
	// Move just the animation node (without moving the shadow)
	this->animationNode->runAction(Sequence::create(
		MoveTo::create(0.5f, peakPosition),
		MoveTo::create(0.5f, Vec2(destAnimPosition.x, peakPosition.y)),
		MoveTo::create(0.5f, destAnimPosition),
		CallFunc::create([=]()
		{
			this->animationNode->setPosition(startAnimPosition);
			this->setPosition(destPosition);

			if (callback != nullptr)
			{
				callback();
			}
		}),
		nullptr
	));

	// Move and scale the shadow separately
	this->shadow->runAction(EaseSineInOut::create(MoveBy::create(0.75f, delta)));
	this->shadow->runAction(Sequence::create(
		ScaleTo::create(0.75f, 0.5f),
		ScaleTo::create(0.75f, 1.0f),
		CallFunc::create([=]()
		{
			this->shadow->setPosition(Vec2::ZERO);
		}),
		nullptr
	));
}
