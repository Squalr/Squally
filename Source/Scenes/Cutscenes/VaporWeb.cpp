#include "VaporWeb.h"

const int VaporWeb::cellColumns = 5;
const int VaporWeb::cellRows = 8;
const int VaporWeb::lineRows = 24;
const int VaporWeb::lineColumns = 49;
const int VaporWeb::specialLineColumns = 5;
const float VaporWeb::backPlane = -8192;
const float VaporWeb::scrollSpeed = 0.5f;

const Color4F VaporWeb::gridColor = Color4F(Color3B(223, 61, 219));
const Color4F VaporWeb::specialGridColor = Color4F(Color3B(61, 138, 223));

VaporWeb* VaporWeb::create()
{
	VaporWeb* instance = new VaporWeb();

	instance->autorelease();

	return instance;
}

VaporWeb::VaporWeb()
{
	this->horizontalLines = new std::vector<Node*>();
	this->verticalLines = new std::vector<Node*>();
	this->distanceGradient = LayerGradient::create(Color4B(0, 0, 0, 0), Color4B(0, 0, 0, 196), Vec2(0.0f, 1.0f));
	this->cells = new std::map<int, Sprite*>();

	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->forestBackground = Sprite::create(Resources::Cutscenes_VaporWeb_Forest_Background);
	this->darkLord = Sprite::create(Resources::Cutscenes_VaporWeb_DarkLord);
	this->dialogPlate = LayerColor::create(Color4B(0, 0, 0, 127), visibleSize.width, 256.0f);
	this->escapeLabel = Label::create("Press esc to exit", Localization::getMainFont(), 28.0f, Size::ZERO, TextHAlignment::LEFT);
	this->escapeLabel->setAnchorPoint(Vec2(0.0f, 0.5f));

	for (int row = 1; row <= VaporWeb::lineRows; row++)
	{
		Vec2 source = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane / row));
		Vec2 destination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporWeb::backPlane / row));

		// Create horizontal line (with offset and post-projection width corrections)
		this->horizontalLines->push_back(this->createLine(
			Vec2(0.0f, source.y - this->getGridOffset()),
			Vec2(visibleSize.width, destination.y - this->getGridOffset()),
			VaporWeb::gridColor
		));
	}
	
	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporWeb::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	for (int column = 0; column <= VaporWeb::lineColumns; column++)
	{
		int adjustedColumn = column - VaporWeb::lineColumns / 2;

		Vec2 source = Vec2((backPlaneWidth / VaporWeb::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
		Vec2 destination = Vec2((frontPlaneWidth / VaporWeb::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

		this->verticalLines->push_back(this->createLine(
			source,
			destination, 
			abs(adjustedColumn) <= VaporWeb::specialLineColumns / 2 ? VaporWeb::specialGridColor : VaporWeb::gridColor)
		);
	}

	for (int column = 0; column < VaporWeb::cellColumns; column++)
	{
		for (int row = 0; row < VaporWeb::cellRows; row++)
		{
			(*this->cells)[this->getCellIndex(row, column)] = Sprite::create(Resources::Cutscenes_VaporWeb_Cell);
			(*this->cells)[this->getCellIndex(row, column)]->setAnchorPoint(Vec2(0.5f, 0.0f));
		}
	}

	this->addChild(InputManager::claimInstance());
	this->forestBackground->setVisible(false);
	this->addChild(this->forestBackground);

	for (auto it = this->horizontalLines->begin(); it != this->horizontalLines->end(); it++)
	{
		(*it)->setVisible(false);
		this->addChild(*it);
	}

	for (auto it = this->verticalLines->begin(); it != this->verticalLines->end(); it++)
	{
		(*it)->setVisible(false);
		this->addChild(*it);
	}

	this->addChild(this->distanceGradient);

	// Add cells symmetrically to preserve proper Z order
	for (int column = 0; column <= VaporWeb::cellColumns / 2; column++)
	{
		for (int row = VaporWeb::cellRows - 1; row >= 0; row--)
		{
			(*this->cells)[this->getCellIndex(row, column)]->setVisible(false);
			this->addChild((*this->cells)[this->getCellIndex(row, column)]);

			if (column != VaporWeb::cellColumns / 2)
			{
				(*this->cells)[this->getCellIndex(row, VaporWeb::cellColumns - column - 1)]->setVisible(false);
				this->addChild((*this->cells)[this->getCellIndex(row, VaporWeb::cellColumns - column - 1)]);
			}
		}
	}

	this->darkLord->setVisible(false);
	this->addChild(this->darkLord);
	this->addChild(this->dialogPlate);
	this->addChild(this->escapeLabel);
}

VaporWeb::~VaporWeb()
{
	delete(this->horizontalLines);
	delete(this->verticalLines);
	delete(this->cells);
}

void VaporWeb::onEnter()
{
	Cutscene::onEnter();

	this->scheduleUpdate();
	this->initializePositions();
	this->initializeListeners();

	this->cutsceneIntro();
}

void VaporWeb::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->forestBackground->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->forestBackground->setPosition(Vec2(visibleSize.width / 2.0f, this->getHorizon()));

	const float noShadowDistance = 96.0f;
	this->distanceGradient->changeWidth(visibleSize.width);
	this->distanceGradient->changeHeight(this->getHorizon() - noShadowDistance + 1.0f); // Add line width
	this->distanceGradient->setPosition(Vec2(visibleSize.width / 2.0f - this->distanceGradient->getContentSize().width / 2.0f, noShadowDistance));

	for (int row = 0; row < VaporWeb::cellRows; row++)
	{
		for (int column = 0; column < VaporWeb::cellColumns; column++)
		{
			const float spacingRow = 2.0f;
			const float spacingColumn = 1.0f;
			const float offset = 3.0f;

			float gridRow = row * spacingRow + offset;
			float gridColumn = VaporWeb::lineColumns / 2 - (VaporWeb::cellColumns / 2) * spacingColumn + column * spacingColumn;

			(*this->cells)[this->getCellIndex(row, column)]->setScale(1.0f - row * 0.1f);
			(*this->cells)[this->getCellIndex(row, column)]->setPosition(this->coordsToLocation(Vec2(gridRow, gridColumn)));
		}
	}

	this->dialogPlate->setPosition(Vec2(visibleSize.width / 2.0f - this->dialogPlate->getContentSize().width / 2.0f, visibleSize.height - this->dialogPlate->getContentSize().height));
	this->escapeLabel->setPosition(Vec2(24.0f, visibleSize.height - 48.0f));
}

void VaporWeb::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void VaporWeb::update(float dt)
{
	FadeScene::update(dt);

	if (InputManager::getInstance()->isPressed(EventKeyboard::KeyCode::KEY_ESCAPE))
	{
		this->endCutscene();
	}
}

void VaporWeb::endCutscene()
{
	NavigationEvents::loadCutscene(NavigationEvents::CutsceneEnum::CutsceneIntroSpace);
}

void VaporWeb::cutsceneIntro()
{
	// Fade in grid
	const float fadeSpeed = 1.0f;
	const float animationSpeedX = 0.45f;
	const float animationVelocityX = 0.003f;
	const float animationAccelerationX = 0.009f;

	const float animationSpeedY = 0.5f;
	const float animationVelocityY = 0.006f;
	const float animationAccelerationY = 0.01f;

	Size visibleSize = Director::getInstance()->getVisibleSize();

	CallFunc* gridFadeIn = CallFunc::create([=]()
	{
		float cumulativeWaitTimeX = 0.0f;
		float cumulativeWaitTimeY = 0.0f;

		for (int rowIndex = 0; rowIndex < VaporWeb::lineRows; rowIndex++)
		{
			int inverseIndex = VaporWeb::lineRows - rowIndex - 1;
			Node* horizontalLine = (*this->horizontalLines)[rowIndex];
			cumulativeWaitTimeX += animationSpeedX + animationVelocityX * rowIndex - ((animationAccelerationX * rowIndex * rowIndex) > animationSpeedX ? animationSpeedX : (animationAccelerationX * rowIndex * rowIndex));

			horizontalLine->setOpacity(0);
			horizontalLine->setVisible(true);
			horizontalLine->runAction(Sequence::create(
				DelayTime::create(cumulativeWaitTimeX),
				FadeIn::create(fadeSpeed),
				nullptr
			));
		}

		for (int columnIndex = VaporWeb::lineColumns / 2; columnIndex >= 0; columnIndex--)
		{
			int inverseIndex = VaporWeb::lineColumns / 2 - columnIndex;
			Node* verticalLine = (*this->verticalLines)[columnIndex];
			cumulativeWaitTimeY += animationSpeedY + animationVelocityY * inverseIndex - ((animationAccelerationY * inverseIndex * inverseIndex) > animationSpeedY ? animationSpeedY : (animationAccelerationY * inverseIndex * inverseIndex));

			verticalLine->setOpacity(0);
			verticalLine->setVisible(true);
			verticalLine->runAction(Sequence::create(
				DelayTime::create(cumulativeWaitTimeY),
				FadeIn::create(fadeSpeed),
				nullptr
			));

			if (columnIndex != VaporWeb::lineColumns / 2)
			{
				Node* verticalLine2 = (*this->verticalLines)[VaporWeb::lineColumns - columnIndex - 1];

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

	CallFunc* dialogBegin = CallFunc::create([=]()
	{

	});

	const float destinationX = visibleSize.width / 2.0f - 96.0f;
	const float destinationY = 128.0f;
	const float flyInTime = 3.0f;
	const float floatDelta = 64.0f;
	const float floatSpeed = 2.0f;

	const float rowDelay = 0.5f;

	CallFunc* darkLordMoveIn = CallFunc::create([=]()
	{
		this->darkLord->setPosition(Vec2(visibleSize.width / 3.0f, visibleSize.height + this->darkLord->getContentSize().height));
		this->darkLord->setVisible(true);
		this->darkLord->runAction(Sequence::create(
			EaseSineOut::create(MoveTo::create(flyInTime, Vec2(destinationX, destinationY + floatDelta))),
			CallFunc::create([=]()
			{
				this->darkLord->runAction(RepeatForever::create(Sequence::create(
					EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(destinationX, destinationY))),
					EaseSineInOut::create(MoveTo::create(floatSpeed, Vec2(destinationX, destinationY + floatDelta))),
					nullptr
				)));
			}),
			nullptr
			));


	});

	CallFunc* fadeInCells = CallFunc::create([=]()
	{
		for (int rowIndex = 0; rowIndex < VaporWeb::cellRows; rowIndex++)
		{
			for (int columnIndex = 0; columnIndex < VaporWeb::cellColumns; columnIndex++)
			{
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->setOpacity(0);
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->setVisible(true);
				(*this->cells)[this->getCellIndex(rowIndex, columnIndex)]->runAction(Sequence::create(
					DelayTime::create(rowIndex * rowDelay),
					FadeIn::create(fadeSpeed),
					nullptr
				));
			}
		}
	});

	CallFunc* triggerNextEvent = CallFunc::create([=]()
	{
		this->cutsceneForest();
	});

	this->runAction(Sequence::create(
		darkLordMoveIn,
		gridFadeIn,
		DelayTime::create(2.0f),
		gridMovementBegin,
		dialogBegin,
		DelayTime::create(1.0f),
		fadeInCells,
		DelayTime::create(rowDelay * VaporWeb::cellRows),
		triggerNextEvent,
		nullptr
	));
}

void VaporWeb::cutsceneForest()
{
	const float fadeSpeed = 1.0f;

	CallFunc* dialogBegin = CallFunc::create([=]()
	{

	});

	CallFunc* fadeInBackground = CallFunc::create([=]()
	{
		this->forestBackground->setOpacity(0);
		this->forestBackground->setVisible(true);
		this->forestBackground->runAction(FadeIn::create(fadeSpeed));
	});

	CallFunc* triggerNextEvent = CallFunc::create([=]()
	{
		this->cutsceneCaverns();
	});

	this->runAction(Sequence::create(
		dialogBegin,
		fadeInBackground,
		DelayTime::create(4.0f),
		triggerNextEvent,
		nullptr
	));
}

void VaporWeb::cutsceneCaverns()
{

}

void VaporWeb::cutsceneIceCaps()
{

}

void VaporWeb::cutsceneObelisk()
{

}

Node* VaporWeb::createLine(Vec2 source, Vec2 destination, Color4F color)
{
	DrawNode* line = DrawNode::create();

	// Instead of just drawing source to dest, offset it by source so that the lines's position can be saved
	line->drawLine(source - source, destination - source, color);
	line->setPosition(source);

	return line;
}

void VaporWeb::runForeverScroll()
{
	for (int lineIndex = 0; lineIndex < VaporWeb::lineRows - 1; lineIndex++)
	{
		Node* current = (*this->horizontalLines)[lineIndex];
		Node* next = (*this->horizontalLines)[lineIndex + 1];
		Vec2 originalPosition = current->getPosition();
		Vec2 nextPosition = next->getPosition();

		CallFunc* returnToStart = CallFunc::create([current, originalPosition] {
			current->setPosition(originalPosition);
		});

		current->runAction(RepeatForever::create(
			Sequence::create(
				MoveTo::create(VaporWeb::scrollSpeed, nextPosition),
				returnToStart,
				nullptr
			)
		));
	}
}

int VaporWeb::getCellIndex(int row, int column)
{
	return VaporWeb::cellRows * column + row;
}

float VaporWeb::getHorizon()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane / VaporWeb::lineRows)).y - this->getGridOffset();
}

float VaporWeb::getGridOffset()
{
	return Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane)).y;
}

Vec2 VaporWeb::coordsToLocation(Vec2 coords)
{
	// Calculate Y position
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 sourceRow = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane / (coords.x + 1.0f)));
	float resultY = sourceRow.y - this->getGridOffset();

	// Calculate X Position
	Vec2 backLineSource = Camera::getDefaultCamera()->project(Vec3(0.0f, 0.0f, VaporWeb::backPlane));
	Vec2 backLineDestination = Camera::getDefaultCamera()->project(Vec3(visibleSize.width, 0.0f, VaporWeb::backPlane));
	float originalBackPlaneWidth = backLineDestination.x - backLineSource.x;
	float backPlaneWidth = visibleSize.width;
	float frontPlaneWidth = (backPlaneWidth / originalBackPlaneWidth) * backPlaneWidth;

	int adjustedColumn = coords.y - VaporWeb::lineColumns / 2;

	Vec2 source = Vec2((backPlaneWidth / VaporWeb::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, this->getHorizon());
	Vec2 destination = Vec2((frontPlaneWidth / VaporWeb::lineColumns) * adjustedColumn + visibleSize.width / 2.0f, 0.0f);

	float resultX = visibleSize.width / 2.0f;

	if (destination.x - source.x != 0.0f)
	{
		float slope = (destination.y - source.y) / (destination.x - source.x);
		float intercept = source.y - slope * source.x;
		resultX = (resultY - intercept) / slope;
	}

	return Vec2(resultX, resultY);
}