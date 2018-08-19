#include "VaporNet.h"

const int VaporNet::cellColumns = 5;
const int VaporNet::cellRows = 10;
const int VaporNet::lineRows = 24;
const int VaporNet::lineColumns = 48;
const float VaporNet::backPlane = -8192;
const float VaporNet::scrollSpeed = 0.5f;

const Color4F VaporNet::gridColor = Color4F(Color3B(223, 61, 219));

VaporNet* VaporNet::create()
{
	VaporNet* instance = new VaporNet();

	instance->autorelease();

	return instance;
}

VaporNet::VaporNet()
{
	this->horizontalLines = new std::vector<Node*>();
	this->verticalLines = new std::vector<Node*>();
	this->cells = new std::map<int, Sprite*>();

	this->gridBackground = Sprite::create(Resources::Cutscenes_VaporNet_Grid);
	Size visibleSize = Director::getInstance()->getVisibleSize();

	for (int row = 1; row <= VaporNet::lineRows; row++)
	{
		Vec2 source = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane / row));
		Vec2 destination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporNet::backPlane / row));

		// Post-projection corrections
		source.x = 0.0f;
		source.y -= this->getGridOffset();
		destination.x = visibleSize.width;
		destination.y -= this->getGridOffset();

		this->horizontalLines->push_back(this->createLine(source, destination));

		// Duplicate the last row (to preserve edges in scrolling effect)
		if (row == VaporNet::lineRows)
		{
			this->horizontalLines->push_back(this->createLine(source, destination));
		}
	}

	for (int column = 0; column <= VaporNet::lineColumns; column++)
	{
		Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane));
		Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporNet::backPlane));
		float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
		float backPlaneWidth = visibleSize.width;
		float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

		int adjustedColumn = column - VaporNet::lineColumns / 2;

		Vec2 source = Vec2((backPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
		Vec2 destination = Vec2((frontPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

		this->verticalLines->push_back(this->createLine(source, destination));
	}

	for (int column = 0; column < VaporNet::cellColumns; column++)
	{
		for (int row = 0; row < VaporNet::cellRows; row++)
		{
			(*this->cells)[this->getCellIndex(row, column)] = Sprite::create(Resources::Cutscenes_VaporNet_Cell);
			(*this->cells)[this->getCellIndex(row, column)]->setAnchorPoint(Vec2(0.5f, 0.0f));
		}
	}

	for (auto it = this->horizontalLines->begin(); it != this->horizontalLines->end(); it++)
	{
		this->addChild(*it);
	}

	for (auto it = this->verticalLines->begin(); it != this->verticalLines->end(); it++)
	{
		this->addChild(*it);
	}

	// Add cells symmetrically to preserve proper Z order
	for (int column = 0; column <= VaporNet::cellColumns / 2; column++)
	{
		for (int row = VaporNet::cellRows - 1; row >= 0; row--)
		{
			this->addChild((*this->cells)[this->getCellIndex(row, column)]);

			if (column != VaporNet::cellColumns / 2)
			{
				this->addChild((*this->cells)[this->getCellIndex(row, VaporNet::cellColumns - column - 1)]);
			}
		}
	}
}

VaporNet::~VaporNet()
{
	delete(this->horizontalLines);
	delete(this->verticalLines);
	delete(this->cells);
}

void VaporNet::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->runForeverScroll();
}

void VaporNet::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gridBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	for (int row = 0; row < VaporNet::cellRows; row++)
	{
		for (int column = 0; column < VaporNet::cellColumns; column++)
		{
			const float spacingRow = 2.0f;
			const float spacingColumn = 1.0f;
			const float offset = 3.0f;

			float gridRow = row * spacingRow + offset;
			float gridColumn = VaporNet::lineColumns / 2 - (VaporNet::cellColumns / 2) * spacingColumn + column * spacingColumn;

			(*this->cells)[this->getCellIndex(row, column)]->setScale(1.0f - row * 0.1f);
			(*this->cells)[this->getCellIndex(row, column)]->setPosition(this->coordsToLocation(Vec2(gridRow, gridColumn)));
		}
	}
}

void VaporNet::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void VaporNet::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void VaporNet::endCutscene()
{
	NavigationEvents::loadMap(Resources::Maps_Isometric_Sanctum);
}

Node* VaporNet::createLine(Vec2 source, Vec2 destination)
{
	DrawNode* line = DrawNode::create();

	// Instead of just drawing source to dest, offset it by source so that the lines's position can be saved
	line->drawLine(source - source, destination - source, VaporNet::gridColor);
	line->setPosition(source);

	return line;
}

void VaporNet::runForeverScroll()
{
	for (int lineIndex = 1; lineIndex < VaporNet::lineRows; lineIndex++)
	{
		Node* previous = (*this->horizontalLines)[lineIndex - 1];
		Node* current = (*this->horizontalLines)[lineIndex];
		Vec2 previousPosition = previous->getPosition();
		Vec2 originalPosition = current->getPosition();

		CallFunc* returnToStart = CallFunc::create([current, originalPosition] {
			current->setPosition(originalPosition);
		});

		current->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(VaporNet::scrollSpeed, previousPosition),
				returnToStart,
				nullptr
			)
		));
	}
}

int VaporNet::getCellIndex(int row, int column)
{
	return VaporNet::cellRows * column + row;
}

float VaporNet::getHorizon()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane / VaporNet::lineRows)).y - this->getGridOffset();
}

float VaporNet::getGridOffset()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane)).y;
}

Vec2 VaporNet::coordsToLocation(Vec2 coords)
{
	// Calculate Y position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 sourceRow = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane / (coords.x + 1.0f)));
	float resultY = sourceRow.y - this->getGridOffset();

	// Calculate X Position
	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporNet::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	int adjustedColumn = coords.y - VaporNet::lineColumns / 2;

	Vec2 source = Vec2((backPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
	Vec2 destination = Vec2((frontPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

	float resultX = visibleSize.width / 2.0f;

	if (destination.x - source.x != 0.0f)
	{
		float slope = (destination.y - source.y) / (destination.x - source.x);
		float intercept = source.y - slope * source.x;
		resultX = (resultY - intercept) / slope;
	}

	return Vec2(resultX, resultY);
}