#include "ScrollPane.h"

const Size ScrollPane::marginSize = Size(8.0f, 4.0f);

ScrollPane* ScrollPane::create(Size initPaneSize, Color4B initBackgroundColor)
{
	ScrollPane* instance = new ScrollPane(initPaneSize, initBackgroundColor);

	instance->autorelease();

	return instance;
}

ScrollPane::ScrollPane(Size initPaneSize, Color4B initBackgroundColor)
{
	this->paneSize = initPaneSize;
	this->backgroundColor = initBackgroundColor;

	this->background = LayerColor::create(this->backgroundColor, initPaneSize.width, initPaneSize.height);
	this->scrollView = ScrollView::create();

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(SCROLLVIEW_DIR_VERTICAL);
	this->scrollView->setSize(Size(initPaneSize.width, initPaneSize.height));
	this->scrollView->setInnerContainerSize(initPaneSize - ScrollPane::marginSize * 2.0f);

	// We override addchild to pass through to the scrollview -- but in this case we want to avoid that
	SmartNode::addChild(this->background);
	SmartNode::addChild(this->scrollView);
}

ScrollPane::~ScrollPane()
{
}

Size ScrollPane::getPaneSize()
{
	return this->paneSize;
}

Size ScrollPane::getContentSize()
{
	return this->scrollView->getInnerContainerSize();
}

void ScrollPane::addChild(Node* child)
{
	this->scrollView->addChild(child);
}

void ScrollPane::fitSizeToContent()
{
	float highestItem = 0.0f;

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		Node* node = *it;

		highestItem = std::max(node->getBoundingBox().getMaxY(), highestItem);
	}

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		Node* node = *it;

		node->setPosition(Vec2(node->getPositionX(), highestItem - node->getPositionY() + this->paneSize.height / 2.0f));
	}

	this->scrollView->setInnerContainerSize(Size(this->paneSize.width - ScrollPane::marginSize.width, highestItem + this->paneSize.height / 2.0f));
}

void ScrollPane::initializePositions()
{
	SmartNode::initializePositions();

	this->background->setPosition(Vec2(-this->paneSize.width / 2.0f, -this->paneSize.height / 2.0f));
	this->scrollView->setPosition(ScrollPane::marginSize);
}

void ScrollPane::initializeListeners()
{
	SmartNode::initializeListeners();
}
