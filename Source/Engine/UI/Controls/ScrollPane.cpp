#include "ScrollPane.h"

#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCClippingRectangleNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCEventListenerMouse.h"
#include "cocos/math/TransformUtils.h"

#include "Engine/Events/MouseEvents.h"
#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/UI/Controls/Slider.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float ScrollPane::DragSpeed = 2.0f;
const float ScrollPane::ScrollSpeed = 64.0f;

ScrollPane* ScrollPane::create(Size paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::Size paddingSize, cocos2d::Size marginSize, Color4B initBackgroundColor)
{
	ScrollPane* instance = new ScrollPane(paneSize, sliderResource, sliderResourceSelected, paddingSize, marginSize, initBackgroundColor);

	instance->autorelease();

	return instance;
}

ScrollPane::ScrollPane(Size paneSize, std::string sliderResource, std::string sliderResourceSelected, cocos2d::Size paddingSize, cocos2d::Size marginSize, Color4B initBackgroundColor)
{
	this->paneSize = paneSize;
	this->paddingSize = paddingSize;
	this->marginSize = marginSize;

	this->initialDragDepth = 0.0f;
	this->background = LayerColor::create(initBackgroundColor, this->paneSize.width + this->marginSize.width * 2.0f, this->paneSize.height + this->marginSize.height * 2.0f);
	this->dragHitbox = ClickableNode::create();
	this->contentClip = ClippingRectangleNode::create(Rect(Vec2::ZERO, this->paneSize));
	this->content = Node::create();

	DrawNode* scrollBounds = DrawNode::create();
	const float scrollTrackWidth = 16.0f;
	const float scrollTrackStopOffset = 24.0f;
	const float dragHorizontalOffset = 32.0f;

	scrollBounds->drawSolidRect(Vec2(-scrollTrackWidth / 2.0f, -this->paneSize.height / 2.0f), Vec2(scrollTrackWidth / 2.0f, this->paneSize.height / 2.0f), Color4F(0.2f, 0.2f, 0.2f, 0.25f));
	scrollBounds->setContentSize(Size(scrollTrackWidth, this->paneSize.height - scrollTrackStopOffset));

	this->scrollBar = Slider::create(scrollBounds, Node::create(), sliderResource, sliderResourceSelected, 0.0f, false);

	this->dragHitbox->setContentSize(Size(this->paneSize.width - dragHorizontalOffset, this->paneSize.height));
	this->content->setContentSize(Size(this->paneSize.width, this->paneSize.height));

	this->dragHitbox->setMouseOverSound("");

	// Note: We override addChild to pass through to the clipping node. Do not call directly for these, call through the parent class.
	super::addChild(this->background);
	super::addChild(this->dragHitbox);
	super::addChild(this->contentClip);
	super::addChild(this->scrollBar);
	this->contentClip->addChild(this->content);
}

ScrollPane::~ScrollPane()
{
}

void ScrollPane::onEnter()
{
	super::onEnter();

	this->setScrollPercentage(0.0f);
}

void ScrollPane::onEnterTransitionDidFinish()
{
	super::onEnterTransitionDidFinish();

	this->updateScrollBounds();
}

void ScrollPane::initializePositions()
{
	super::initializePositions();

	this->background->setPosition(Vec2(-this->paneSize.width / 2.0f - ScrollPane::marginSize.width, -this->paneSize.height / 2.0f - ScrollPane::marginSize.height));
	this->contentClip->setPosition(Vec2(-this->paneSize.width / 2.0f, -this->paneSize.height / 2.0f));
	this->content->setPosition(Vec2(this->paneSize.width / 2.0f, this->paneSize.height));
	this->scrollBar->setPosition(Vec2(this->paneSize.width / 2.0f, 0.0f));
}

void ScrollPane::initializeListeners()
{
	super::initializeListeners();

	this->scrollBar->setProgressUpdateCallback([=](float progress)
	{
		this->setScrollPercentage(progress, false);
	});

	this->dragHitbox->setMouseScrollCallback([=](ClickableNode*, MouseEvents::MouseEventArgs* args)
	{
		this->scrollBy(args->scrollDelta.y * ScrollPane::ScrollSpeed);
	});

	this->dragHitbox->setMouseDownCallback([=](ClickableNode*, MouseEvents::MouseEventArgs* args)
	{
		this->initialDragDepth = this->getScrollDepth();
	});

	this->dragHitbox->setMouseDragCallback([=](ClickableNode*, MouseEvents::MouseEventArgs* args)
	{
		float dragDelta = (args->mouseCoords.y - args->mouseInitialCoords.y) * ScrollPane::DragSpeed;

		this->scrollTo(this->initialDragDepth + dragDelta);
	});
}

void ScrollPane::setScrollPercentage(float percentage, bool updateScrollBars)
{
	this->scrollTo((this->maxScrollDepth - this->minScrollDepth) * percentage, updateScrollBars);
}

void ScrollPane::scrollBy(float delta, bool updateScrollBars)
{
	this->scrollTo(this->getScrollDepth() + delta, updateScrollBars);
}

void ScrollPane::scrollTo(float position, bool updateScrollBars)
{
	this->content->setPositionY(MathUtils::clamp(position + this->minScrollDepth, this->minScrollDepth, this->maxScrollDepth));

	if (updateScrollBars && this->maxScrollDepth - this->minScrollDepth != 0.0f)
	{
		this->scrollBar->setProgress(this->getScrollPercentage());
	}
}

float ScrollPane::getScrollPercentage()
{
	float denominator = this->maxScrollDepth - this->minScrollDepth;

	return denominator == 0.0f ? 0.0f : (this->content->getPositionY() - this->minScrollDepth) / denominator;
}

float ScrollPane::getScrollDepth()
{
	return this->content->getPositionY() - this->minScrollDepth;
}

Size ScrollPane::getPaneSize()
{
	return this->paneSize;
}

void ScrollPane::addChild(Node* child)
{
	this->content->addChild(child);

	this->updateScrollBounds();
}

void ScrollPane::removeChild(Node* child, bool cleanup)
{
	this->content->removeChild(child, cleanup);

	this->updateScrollBounds();
}

void ScrollPane::removeAllChildren()
{
	this->content->removeAllChildren();

	this->updateScrollBounds();
}

void ScrollPane::updateScrollBounds()
{
	this->minScrollDepth = this->paneSize.height - this->paddingSize.height;

	auto children = this->content->getChildren();
	float discoveredLowestItem = 0.0f;

	for (auto it = children.begin(); it != children.end(); it++)
	{
		discoveredLowestItem = std::min(discoveredLowestItem, (*it)->getBoundingBox().getMinY() - ((*it)->getContentSize().height / 2.0f * GameUtils::getScale(*it)));
	}

	this->maxScrollDepth = std::max(this->minScrollDepth, -discoveredLowestItem) + this->paddingSize.height;
}
