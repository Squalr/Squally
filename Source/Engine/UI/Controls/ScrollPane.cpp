#include "ScrollPane.h"

#include "cocos/2d/CCAction.h"
#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCClippingNode.h"
#include "cocos/2d/CCDrawNode.h"
#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCNode.h"
#include "cocos/math/TransformUtils.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/GameUtils.h"
#include "Engine/Utils/MathUtils.h"
#include "Engine/UI/Controls/Slider.h"

using namespace cocos2d;
using namespace cocos2d::ui;

const float ScrollPane::DragSpeed = 2.0f;
const float ScrollPane::ScrollSpeed = 64.0f;
const float ScrollPane::ScrollTrackWidth = 16.0f;
const float ScrollPane::ScrollTrackStopOffset = 48.0f;
const float ScrollPane::ScrollTotalWidth = 32.0f;

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
	this->updateSuspended = false;

	this->initialDragDepth = 0.0f;
	this->customBackground = DrawNode::create();
	this->background = LayerColor::create(initBackgroundColor, this->paneSize.width + this->marginSize.width * 2.0f, this->paneSize.height + this->marginSize.height * 2.0f);
	this->dragHitbox = ClickableNode::create();
	this->clipStencil = DrawNode::create();
	this->contentClip = ClippingNode::create(this->clipStencil);
	this->content = Node::create();
	this->scrollBounds = DrawNode::create();
	this->scrollBounds->drawSolidRect(Vec2(-ScrollPane::ScrollTrackWidth / 2.0f, -(this->paneSize.height - ScrollPane::ScrollTrackStopOffset) / 2.0f), Vec2(ScrollPane::ScrollTrackWidth / 2.0f, (this->paneSize.height - ScrollPane::ScrollTrackStopOffset) / 2.0f), Color4F(0.2f, 0.2f, 0.2f, 0.25f));
	this->scrollBounds->setContentSize(Size(ScrollPane::ScrollTrackWidth, this->paneSize.height - ScrollPane::ScrollTrackStopOffset));
	this->scrollBar = Slider::create(this->scrollBounds, Node::create(), sliderResource, sliderResourceSelected, 0.0f, false);

	this->dragHitbox->setContentSize(Size(this->paneSize.width - ScrollTotalWidth, this->paneSize.height));
	this->content->setContentSize(Size(this->paneSize.width - this->paddingSize.width * 2.0f - ScrollPane::ScrollTrackWidth / 2.0f, this->paneSize.height - this->paddingSize.height * 2.0f));

	this->dragHitbox->setMouseOverSound("");

	this->clipStencil->drawSolidRect(Vec2::ZERO, this->paneSize, Color4F::GREEN);

	// Enable to debug clipping:
	// super::addChild(this->clipStencil);

	// Note: We override addChild to pass through to the clipping node. Do not call directly for these, call through the parent class.
	super::addChild(this->background);
	super::addChild(this->customBackground);
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

	this->dragHitbox->neverHandle();

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

	this->customBackground->setPosition(Vec2(-this->paneSize.width / 2.0f - ScrollPane::marginSize.width, -this->paneSize.height / 2.0f - ScrollPane::marginSize.height));
	this->background->setPosition(Vec2(-this->paneSize.width / 2.0f - ScrollPane::marginSize.width, -this->paneSize.height / 2.0f - ScrollPane::marginSize.height));
	this->dragHitbox->setPosition(Vec2(-ScrollPane::ScrollTotalWidth / 2.0f, 0.0f));
	this->contentClip->setPosition(Vec2(-this->paneSize.width / 2.0f, -this->paneSize.height / 2.0f));
	this->content->setPosition(Vec2(this->paneSize.width / 2.0f - ScrollPane::ScrollTotalWidth / 2.0f, this->paneSize.height));
	this->scrollBar->setPosition(Vec2(this->paneSize.width / 2.0f + this->marginSize.width - ScrollPane::ScrollTrackWidth, 0.0f));
}

void ScrollPane::initializeListeners()
{
	super::initializeListeners();

	this->scrollBar->setProgressUpdateCallback([=](float progress)
	{
		this->setScrollPercentage(progress, false);
	});

	this->dragHitbox->setMouseScrollCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->scrollBy(args->scrollDelta.y * ScrollPane::ScrollSpeed);
	});

	this->dragHitbox->setMouseDownCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->initialDragDepth = this->getScrollDepth();
	});

	this->dragHitbox->setMouseDragCallback([=](InputEvents::MouseEventArgs* args)
	{
		float dragDelta = (args->mouseCoords.y - args->mouseInitialCoords.y) * ScrollPane::DragSpeed;

		this->scrollTo(this->initialDragDepth + dragDelta);
	});
}

void ScrollPane::enableInteraction()
{
	this->scrollBar->enableInteraction();
	this->dragHitbox->enableInteraction();
}

void ScrollPane::disableInteraction()
{
	this->scrollBar->disableInteraction();
	this->dragHitbox->disableInteraction();
}

void ScrollPane::setBackgroundColor(cocos2d::Color4B backgroundColor)
{
	this->background->initWithColor(backgroundColor, this->paneSize.width + this->marginSize.width * 2.0f, this->paneSize.height + this->marginSize.height * 2.0f);
}

void ScrollPane::renderCustomBackground(std::function<void(cocos2d::DrawNode* customBackground, cocos2d::Size paneSize, cocos2d::Size paddingSize, cocos2d::Size marginSize)> drawFunc)
{
	if (drawFunc != nullptr)
	{
		this->background->setVisible(false);

		drawFunc(this->customBackground, this->paneSize, this->paddingSize, this->marginSize);
	}
}

void ScrollPane::setScrollPercentage(float percentage, bool updateScrollBars, float duration)
{
	this->scrollTo((this->maxScrollDepth - this->minScrollDepth) * percentage, updateScrollBars, duration);
}

void ScrollPane::scrollBy(float delta, bool updateScrollBars, float duration)
{
	this->scrollTo(this->getScrollDepth() + delta, updateScrollBars, duration);
}

void ScrollPane::scrollToCenter(Node* target, bool updateScrollBars, float duration)
{
	this->scrollTo(-target->getPositionY() - this->getPaneSize().height / 2.0f, updateScrollBars, duration);
}

void ScrollPane::scrollTo(float position, bool updateScrollBars, float duration)
{
	if (duration <= 0.0f)
	{
		this->content->setPositionY(MathUtils::clamp(position + this->minScrollDepth, this->minScrollDepth, this->maxScrollDepth));

		if (updateScrollBars && this->maxScrollDepth - this->minScrollDepth != 0.0f)
		{
			this->scrollBar->setProgress(this->getScrollPercentage());
		}
	}
	else
	{
		this->content->runAction(Sequence::create(
			MoveTo::create(duration, Vec2(this->content->getPositionX(), MathUtils::clamp(position + this->minScrollDepth, this->minScrollDepth, this->maxScrollDepth))),
			CallFunc::create([=]()
			{
				if (updateScrollBars && this->maxScrollDepth - this->minScrollDepth != 0.0f)
				{
					this->scrollBar->setProgress(this->getScrollPercentage());
				}
			}),
			nullptr
		));

		int ticks = int(duration / (1.0f / 60.0f));
		
		this->content->runAction(
			Repeat::create(Sequence::create(
				DelayTime::create(1.0f / 60.0f),
				CallFunc::create([=]()
				{
					if (updateScrollBars && this->maxScrollDepth - this->minScrollDepth != 0.0f)
					{
						this->scrollBar->setProgress(this->getScrollPercentage());
					}
				}),
				nullptr
			), ticks)
		);
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
	if (this->updateSuspended)
	{
		return;
	}

	this->minScrollDepth = this->paneSize.height - this->paddingSize.height;

	float discoveredLowestItem = this->getLowestChild(this->content->getChildren());

	this->maxScrollDepth = std::max(this->minScrollDepth, -discoveredLowestItem) + this->paddingSize.height;
	this->setScrollPercentage(this->getScrollPercentage());
}

void ScrollPane::suspendUpdate()
{
	this->updateSuspended = true;
}

void ScrollPane::resumeUpdate()
{
	this->updateSuspended = false;

	this->updateScrollBounds();
}

float ScrollPane::getLowestChild(Vector<cocos2d::Node*>& children, float lowestItem)
{
	for (auto next : children)
	{
		if (GameUtils::isVisibleUntil<ScrollPane>(next))
		{
			lowestItem = std::min(lowestItem, next->getBoundingBox().getMinY() - (next->getContentSize().height / 2.0f * GameUtils::getUniformScale(next)));

			// Recurse
			lowestItem = this->getLowestChild(next->getChildren(), lowestItem);
		}
	}

	return lowestItem;
}
