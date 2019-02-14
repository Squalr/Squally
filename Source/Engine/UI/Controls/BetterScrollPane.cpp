#include "BetterScrollPane.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCEventListenerMouse.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float BetterScrollPane::scrollSpeed = 64.0f;

BetterScrollPane* BetterScrollPane::create(Size paneSize, cocos2d::Size paddingSize, cocos2d::Size marginSize, Color4B initBackgroundColor)
{
	BetterScrollPane* instance = new BetterScrollPane(paneSize, paddingSize, marginSize, initBackgroundColor);

	instance->autorelease();

	return instance;
}

BetterScrollPane::BetterScrollPane(Size paneSize, cocos2d::Size paddingSize, cocos2d::Size marginSize, Color4B initBackgroundColor)
{
	this->paneSize = paneSize;
	this->paddingSize = paddingSize;
	this->marginSize = marginSize;

	this->background = LayerColor::create(initBackgroundColor, this->paneSize.width + this->marginSize.width * 2.0f, this->paneSize.height + this->marginSize.height * 2.0f);
	this->contentClip = ClippingRectangleNode::create(Rect(Vec2::ZERO, this->paneSize));
	this->content = Node::create();

	this->content->setContentSize(Size(this->paneSize.width, this->paneSize.height));

	// Note: We override addChild to pass through to the clipping node. Do not call directly for these, call through the parent class.
	super::addChild(this->background);
	super::addChild(this->contentClip);
	this->contentClip->addChild(this->content);
}

BetterScrollPane::~BetterScrollPane()
{
}

void BetterScrollPane::onEnter()
{
	super::onEnter();

	this->updateScrollBounds();
	this->setScrollPercentage(0.0f);
}

void BetterScrollPane::initializePositions()
{
	super::initializePositions();

	this->background->setPosition(Vec2(-this->paneSize.width / 2.0f - BetterScrollPane::marginSize.width, -this->paneSize.height / 2.0f - BetterScrollPane::marginSize.height));
	this->contentClip->setPosition(Vec2(-this->paneSize.width / 2.0f, -this->paneSize.height / 2.0f));
	this->content->setPosition(Vec2(this->paneSize.width / 2.0f, this->paneSize.height));
}

void BetterScrollPane::initializeListeners()
{
	super::initializeListeners();

	EventListenerMouse* mouseScrollListener = EventListenerMouse::create();

	mouseScrollListener->onMouseScroll = CC_CALLBACK_1(BetterScrollPane::onMouseScroll, this);
	mouseScrollListener->onMouseMove = CC_CALLBACK_1(BetterScrollPane::onScrollViewMouseMove, this);

	this->addEventListener(mouseScrollListener);
}

void BetterScrollPane::setScrollPercentage(float percentage)
{
	this->scrollTo((this->maxScrollDepth - this->minScrollDepth) * percentage);
}

void BetterScrollPane::scrollBy(float delta)
{
	this->scrollTo(this->content->getPositionY() + delta);
}

void BetterScrollPane::scrollTo(float position)
{
	this->content->setPositionY(MathUtils::clamp(position, this->minScrollDepth, this->maxScrollDepth));
}

Size BetterScrollPane::getPaneSize()
{
	return this->paneSize;
}

void BetterScrollPane::addChild(Node* child)
{
	this->content->addChild(child);

	this->updateScrollBounds();
}

void BetterScrollPane::removeChild(Node* child, bool cleanup)
{
	this->content->removeChild(child, cleanup);

	this->updateScrollBounds();
}

void BetterScrollPane::removeAllChildren()
{
	this->content->removeAllChildren();

	this->updateScrollBounds();
}

void BetterScrollPane::updateScrollBounds()
{
	this->minScrollDepth = this->paneSize.height - this->paddingSize.height;

	auto children = this->content->getChildren();
	float discoveredLowestItem = 0.0f;

	for (auto it = children.begin(); it != children.end(); it++)
	{
		discoveredLowestItem = std::min(discoveredLowestItem, (*it)->getBoundingBox().getMinY());
	}

	this->maxScrollDepth = std::max(this->minScrollDepth, -discoveredLowestItem) + this->paddingSize.height;
}

void BetterScrollPane::onMouseScroll(EventMouse* event)
{
	if (GameUtils::isVisible(this) && GameUtils::intersects(this->background, Vec2(event->getCursorX(), event->getCursorY())))
	{
		this->scrollBy(event->getScrollY() * BetterScrollPane::scrollSpeed);

		MouseEvents::TriggerClickableMouseOutEvent();
		MouseEvents::TriggerMouseScroll();
	}
}

void BetterScrollPane::onScrollViewMouseMove(EventMouse* event)
{
	if (GameUtils::isVisible(this) && GameUtils::intersects(this->background, Vec2(event->getCursorX(), event->getCursorY())))
	{
		// Start drag animation
		if (event->getMouseButton() == EventMouse::MouseButton::BUTTON_LEFT)
		{
			MouseEvents::TriggerDragEvent();
			MouseEvents::TriggerClickableMouseOutEvent();
		}
	}
}
