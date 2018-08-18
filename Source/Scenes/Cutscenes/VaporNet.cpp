#include "VaporNet.h"

const int VaporNet::cellColumns = 5;
const int VaporNet::cellRows = 8;
const int VaporNet::lineRows = 24;
const int VaporNet::lineColumns = 48;
const float VaporNet::backPlane = -8192;

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
		source.y -= this->getGridHeight();
		destination.x = visibleSize.width;
		destination.y -= this->getGridHeight();

		DrawNode* line = DrawNode::create();

		line->drawLine(source, destination, VaporNet::gridColor);

		this->horizontalLines->push_back(line);
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

		DrawNode* line = DrawNode::create();

		line->drawLine(source, destination, VaporNet::gridColor);

		this->verticalLines->push_back(line);
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
}

void VaporNet::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->gridBackground->setPosition(Vec2(visibleSize.width / 2.0f, visibleSize.height / 2.0f));

	for (int row = 0; row < VaporNet::cellRows; row++)
	{
		for (int column = 0; column < VaporNet::cellColumns; column++)
		{
			const float spacingRow = 4.0f;
			const float spacingColumn = 1.0f;
			const float offset = 3.0f;

			float gridRow = row * spacingRow + offset;
			float gridColumn = VaporNet::lineColumns / 2 - (VaporNet::cellColumns / 2) * spacingColumn + column * spacingColumn;

			(*this->cells)[this->getCellIndex(row, column)]->setScale(1.0f - row * 0.06f);
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

int VaporNet::getCellIndex(int row, int column)
{
	return VaporNet::cellRows * column + row;
}

float VaporNet::getHorizon()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane / VaporNet::lineRows)).y - this->getGridHeight();
}

float VaporNet::getGridHeight()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane)).y;
}

Vec2 VaporNet::coordsToLocation(Vec2 coords)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporNet::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporNet::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	int adjustedColumn = coords.y - VaporNet::lineColumns / 2;

	Vec2 source = Vec2((backPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
	Vec2 destination = Vec2((frontPlaneWidth / VaporNet::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

	return destination + (source - destination) * (coords.x / VaporNet::lineRows);
}