#include "ScrollPane.h"

const Size ScrollPane::marginSize = Size(24.0f, 24.0f);
const float ScrollPane::scrollSpeed = 64.0f;

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

	EventListenerMouse* mouseScrollListener = EventListenerMouse::create();
	EventListenerMouse* mouseMoveListener = EventListenerMouse::create();

	mouseScrollListener->onMouseScroll = CC_CALLBACK_1(ScrollPane::onMouseScroll, this);
	mouseScrollListener->onMouseMove = CC_CALLBACK_1(ScrollPane::onScrollViewMouseMove, this);

	this->scrollView->addEventListenerScrollView(mouseMoveListener, nullptr);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseScrollListener, this);
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
	float newHeight = 0.0f;

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		newHeight = std::max((*it)->getBoundingBox().getMaxY(), newHeight);
	}

	float minItem = newHeight;

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		minItem = std::min((*it)->getBoundingBox().getMinY(), minItem);
	}

	newHeight += minItem;

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		Node* node = *it;

		node->setPosition(Vec2(node->getPositionX(), newHeight - node->getPositionY()));
	}

	this->scrollView->setInnerContainerSize(Size(this->paneSize.width, newHeight));
}

void ScrollPane::onMouseScroll(EventMouse* event)
{
	if (GameUtils::isVisible(this))
	{
		this->scrollView->scrollChildren(Vec2(0.0f, event->getScrollY() * ScrollPane::scrollSpeed));

		MouseEvents::TriggerClickableMouseOutEvent();
		MouseEvents::TriggerMouseScroll();
	}
}

void ScrollPane::onScrollViewMouseMove(EventMouse* event)
{
	if (GameUtils::isVisible(this) && GameUtils::intersectsV2(this->background, Vec2(event->getCursorX(), event->getCursorY())))
	{
		// Start drag animation
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			MouseEvents::TriggerDragEvent();
			MouseEvents::TriggerClickableMouseOutEvent();
		}
	}
}
