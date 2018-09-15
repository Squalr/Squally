#include "ScrollPane.h"

const Size ScrollPane::marginSize = Size(24.0f, 24.0f);
const float ScrollPane::scrollSpeed = 48.0f;

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

	this->background = LayerColor::create(this->backgroundColor, initPaneSize.width + marginSize.width * 2.0f, initPaneSize.height + marginSize.height * 2.0f);
	this->scrollView = ScrollView::create();

	this->scrollView->setAnchorPoint(Vec2(0.5f, 0.5f));
	this->scrollView->setDirection(SCROLLVIEW_DIR_VERTICAL);
	this->scrollView->setSize(Size(initPaneSize.width, initPaneSize.height));

	// We override addchild to pass through to the scrollview -- but in this case we want to avoid that
	SmartNode::addChild(this->background);
	SmartNode::addChild(this->scrollView);
}

ScrollPane::~ScrollPane()
{
}

void ScrollPane::initializePositions()
{
	SmartNode::initializePositions();

	this->background->setPosition(Vec2(-this->paneSize.width / 2.0f - ScrollPane::marginSize.width, -this->paneSize.height / 2.0f - ScrollPane::marginSize.height));
}

void ScrollPane::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseScroll = CC_CALLBACK_1(ScrollPane::onMouseScroll, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
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

	this->scrollView->setInnerContainerSize(Size(this->paneSize.width, highestItem + this->paneSize.height / 2.0f));
}

void ScrollPane::onMouseScroll(EventMouse* event)
{
	this->scrollView->scrollChildren(Vec2(0.0f, event->getScrollY() * ScrollPane::scrollSpeed));
}
