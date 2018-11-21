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
	this->scrollView->setScrollBarAutoHideEnabled(false);
	this->scrollView->setScrollBarOpacity(196);
	this->scrollView->setCascadeOpacityEnabled(true);
	this->setCascadeOpacityEnabled(true);

	// We override addchild to pass through to the scrollview -- but in this case we want to avoid that
	SmartNode::addChild(this->background);
	SmartNode::addChild(this->scrollView);
}

ScrollPane::~ScrollPane()
{
}

void ScrollPane::onEnter()
{
	SmartNode::onEnter();

	this->scrollView->scrollToPercentVertical(100.0f, 0.0f, false);
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
	this->addEventListener(mouseScrollListener);
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

void ScrollPane::removeChild(Node* child, bool cleanup)
{
	this->scrollView->removeChild(child, cleanup);
}

void ScrollPane::removeAllChildren()
{
	this->scrollView->removeAllChildren();
}

void ScrollPane::fitSizeToContent(Rect padding)
{
	Vec2 oldScrollDepth = this->scrollView->getInnerContainerPosition();
	bool firstLoad = this->scrollView->getScrolledPercentVertical() == 0.0f;
	float minHeight = this->scrollView->getChildren().size() > 0 ? (this->scrollView->getChildren().front()->getPositionY() - this->scrollView->getChildren().front()->getContentSize().height / 2.0f) : 0.0f;
	float maxHeight = this->paneSize.height;

	for (auto it = this->scrollView->getChildren().begin(); it != this->scrollView->getChildren().end(); it++)
	{
		(*it)->setPosition((*it)->getPosition() + padding.origin);
		minHeight = std::min((*it)->getPositionY() - (*it)->getContentSize().height / 2.0f, minHeight);
		maxHeight = std::max((*it)->getPositionY() + (*it)->getContentSize().height / 2.0f, maxHeight);
	}
	
	this->scrollView->setInnerContainerSize(Size(this->paneSize.width + padding.origin.y + padding.size.width, maxHeight + minHeight + padding.origin.x + padding.size.height));
	this->scrollView->setInnerContainerPosition(oldScrollDepth);

	this->scrollView->scrollToPercentVertical(firstLoad ? 0.0f : this->scrollView->getScrolledPercentVertical(), 0.0f, false);
}

void ScrollPane::onMouseScroll(EventMouse* event)
{
	if (GameUtils::isVisible(this) && GameUtils::intersectsV2(this->background, Vec2(event->getCursorX(), event->getCursorY())))
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
