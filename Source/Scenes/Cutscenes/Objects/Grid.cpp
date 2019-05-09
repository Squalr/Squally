#include "Grid.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCCamera.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"

#include "Scenes/Cutscenes/Objects/GridItem.h"

using namespace cocos2d;

const float Grid::backPlane = -8192.0f;
const int Grid::lineRows = 24;
const int Grid::lineColumns = 49;
const int Grid::specialLineColumns = 5;
const float Grid::scrollSpeed = 0.35f;
const float Grid::objectSpeed = 1.0f / Grid::scrollSpeed;

const Color4F Grid::gridColor = Color4F(Color3B(223, 61, 219));
const Color4F Grid::specialGridColor = Color4F(Color3B(61, 138, 223));

const std::string Grid::ScheduleKeyScrollGridItems = "SCHEDULE_KEY_SCROLL_GRID_OBJECTS";

Grid* Grid::create()
{
	Grid* instance = new Grid();

	instance->autorelease();

	return instance;
}

Grid::Grid()
{
	this->horizontalLines = std::vector<Node*>();
	this->verticalLines = std::vector<Node*>();
	this->gridObjects = std::vector<GridItem*>();
	this->distanceGradient = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 196), Vec2(0.0f, 1.0f));

	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int row = 1; row <= Grid::lineRows; row++)
	{
		Vec2 source = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane / row));
		Vec2 destination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, Grid::backPlane / row));

		// Create horizontal line (with offset and post-projection width corrections)
		this->horizontalLines.push_back(this->createLine(
			Vec2(0.0f, source.y - this->getGridOffset()),
			Vec2(visibleSize.width, destination.y - this->getGridOffset()),
			Grid::gridColor
		));
	}

	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, Grid::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	for (int column = 0; column <= Grid::lineColumns; column++)
	{
		int adjustedColumn = column - Grid::lineColumns / 2;

		Vec2 source = Vec2((backPlaneWidth / Grid::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
		Vec2 destination = Vec2((frontPlaneWidth / Grid::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

		this->verticalLines.push_back(this->createLine(
			source,
			destination,
			abs(adjustedColumn) <= Grid::specialLineColumns / 2 ? Grid::specialGridColor : Grid::gridColor)
		);
	}

	for (auto it = this->horizontalLines.begin(); it != this->horizontalLines.end(); it++)
	{
		(*it)->setVisible(false);
		this->addChild(*it);
	}

	for (auto it = this->verticalLines.begin(); it != this->verticalLines.end(); it++)
	{
		(*it)->setVisible(false);
		this->addChild(*it);
	}

	this->addChild(this->distanceGradient);
}

Grid::~Grid()
{
}

void Grid::onEnter()
{
	super::onEnter();

	CallFunc* gridFadeIn = CallFunc::create([=]()
	{
		// Fade in grid
		const float fadeSpeed = 1.0f;
		const float animationSpeedX = 0.45f;
		const float animationVelocityX = 0.003f;
		const float animationAccelerationX = 0.009f;

		const float animationSpeedY = 0.5f;
		const float animationVelocityY = 0.006f;
		const float animationAccelerationY = 0.01f;

		float cumulativeWaitTimeX = 0.0f;
		float cumulativeWaitTimeY = 0.0f;

		for (int rowIndex = 0; rowIndex < Grid::lineRows; rowIndex++)
		{
			Node* horizontalLine = this->horizontalLines[rowIndex];
			cumulativeWaitTimeX += animationSpeedX + animationVelocityX * rowIndex - ((animationAccelerationX * rowIndex * rowIndex) > animationSpeedX ? animationSpeedX : (animationAccelerationX * rowIndex * rowIndex));

			horizontalLine->setOpacity(0);
			horizontalLine->setVisible(true);
			horizontalLine->runAction(Sequence::create(
				DelayTime::create(cumulativeWaitTimeX),
				FadeIn::create(fadeSpeed),
				nullptr
			));
		}

		for (int columnIndex = Grid::lineColumns / 2; columnIndex >= 0; columnIndex--)
		{
			int inverseIndex = Grid::lineColumns / 2 - columnIndex;
			Node* verticalLine = this->verticalLines[columnIndex];
			cumulativeWaitTimeY += animationSpeedY + animationVelocityY * inverseIndex - ((animationAccelerationY * inverseIndex * inverseIndex) > animationSpeedY ? animationSpeedY : (animationAccelerationY * inverseIndex * inverseIndex));

			verticalLine->setOpacity(0);
			verticalLine->setVisible(true);
			verticalLine->runAction(Sequence::create(
				DelayTime::create(cumulativeWaitTimeY),
				FadeIn::create(fadeSpeed),
				nullptr
			));

			if (columnIndex != Grid::lineColumns / 2)
			{
				Node* verticalLine2 = this->verticalLines[Grid::lineColumns - columnIndex - 1];

				verticalLine2->setOpacity(0);
				verticalLine2->setVisible(true);
				verticalLine2->runAction(Sequence::create(
					DelayTime::create(cumulativeWaitTimeY),
					FadeIn::create(fadeSpeed),
					nullptr
				));
			}
		}
	});

	CallFunc* gridMovementBegin = CallFunc::create([=]()
	{
		this->runForeverScroll();
	});

	this->runAction(Sequence::create(
		gridFadeIn,
		DelayTime::create(2.0f),
		gridMovementBegin,
		nullptr
	));

	this->scheduleUpdate();
}

void Grid::initializePositions()
{
	super::initializePositions();
	
	Size visibleSize = Director::getInstance()->getVisibleSize();

	const float noShadowDistance = 96.0f;
	this->distanceGradient->changeWidth(visibleSize.width);
	this->distanceGradient->changeHeight(this->getHorizon() - noShadowDistance + 1.0f); // Add line width
	this->distanceGradient->setPosition(Vec2(visibleSize.width / 2.0f - this->distanceGradient->getContentSize().width / 2.0f, noShadowDistance));
}

void Grid::addGridItem(GridItem* gridObject)
{
	this->gridObjects.push_back(gridObject);

	this->addChild(gridObject);
}

Node* Grid::createLine(Vec2 source, Vec2 destination, Color4F color)
{
	DrawNode* line = DrawNode::create();

	// Instead of just drawing source to dest, offset it by source so that the lines's position can be saved
	line->drawLine(source - source, destination - source, color);
	line->setPosition(source);

	return line;
}

void Grid::runForeverScroll()
{
	for (int lineIndex = 0; lineIndex < Grid::lineRows - 1; lineIndex++)
	{
		Node* current = this->horizontalLines[lineIndex];
		Node* next = this->horizontalLines[lineIndex + 1];
		Vec2 originalPosition = current->getPosition();
		Vec2 nextPosition = next->getPosition();

		CallFunc* returnToStart = CallFunc::create([current, originalPosition] {
			current->setPosition(originalPosition);
		});

		current->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(Grid::scrollSpeed, nextPosition),
				returnToStart,
				nullptr
			)
		));
	}
}

void Grid::update(float dt)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (auto it = this->gridObjects.begin(); it != this->gridObjects.end(); it++)
	{
		Vec2 coords = (*it)->getCoords();
		float inverseX = ((float)Grid::lineRows - coords.x);
		float centerDelta = std::abs(coords.y - (float)Grid::lineColumns);

		(*it)->setCoords(coords + Vec2(Grid::objectSpeed * dt, 0.0f));
		(*it)->setScale(std::min(inverseX / (float)Grid::lineRows, 1.5f));
		(*it)->setPosition(this->coordsToLocation(Vec2(coords.x, coords.y)));

		(*it)->setLocalZOrder(inverseX * visibleSize.width + centerDelta);
	}
	
	// Remove off-screen objects
	auto removed = std::remove_if(this->gridObjects.begin(), this->gridObjects.end(), [=](GridItem* object)
	{
		if (object->getScale() <= 0.0f)
		{
			this->removeChild(object);
			return true;
		}

		return false;
	});

	this->gridObjects.erase(removed, this->gridObjects.end());
}

float Grid::getHorizon()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane / Grid::lineRows)).y - this->getGridOffset();
}

float Grid::getGridOffset()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane)).y;
}

Vec2 Grid::coordsToLocation(Vec2 coords)
{
	// Prevent going too far off screen
	if (coords.x < -5.0f)
	{
		coords.x = -5.0f;
	}

	// Calculate Y position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 sourceRow = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane / (coords.x + 1.0f)));
	float resultY = sourceRow.y - this->getGridOffset();

	// Calculate X Position
	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, Grid::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, Grid::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	float adjustedColumn = coords.y - Grid::lineColumns / 2;

	Vec2 source = Vec2((backPlaneWidth / (float)Grid::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
	Vec2 destination = Vec2((frontPlaneWidth / (float)Grid::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

	float resultX = visibleSize.width / 2.0f;

	if (destination.x - source.x != 0.0f)
	{
		float slope = (destination.y - source.y) / (destination.x - source.x);
		float intercept = source.y - slope * source.x;
		resultX = (resultY - intercept) / slope;
	}

	return Vec2(resultX, resultY);
}
