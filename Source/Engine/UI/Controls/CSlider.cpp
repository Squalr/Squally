#include "CSlider.h"

#include "cocos/2d/CCSprite.h"
#include "cocos/2d/CCClippingRectangleNode.h"

#include "Engine/UI/Controls/MenuSprite.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

CSlider* CSlider::create(float progress)
{
	CSlider* instance = new CSlider(progress);

	instance->autorelease();

	return instance;
}

CSlider::CSlider(float progress)
{
	this->progressUpdateEvent = nullptr;

	this->frame = Sprite::create(UIResources::Menus_OptionsMenu_SliderFrame);
	this->progressBar = MenuSprite::create(UIResources::Menus_OptionsMenu_SliderFill, UIResources::Menus_OptionsMenu_SliderFill);
	this->progressClip = ClippingRectangleNode::create(Rect(0, -32, this->progressBar->getContentSize().width, 64));
	this->slide = MenuSprite::create(UIResources::Menus_OptionsMenu_Slide, UIResources::Menus_OptionsMenu_Slide);

	this->setCascadeOpacityEnabled(true);
	this->progressClip->setCascadeOpacityEnabled(true);
	this->setProgress(progress);

	this->progressBar->setMouseDownCallback(CC_CALLBACK_2(CSlider::onDrag, this));
	this->slide->setMouseDragCallback(CC_CALLBACK_2(CSlider::onDrag, this));

	this->progressClip->addChild(this->progressBar);

	this->addChild(this->frame);
	this->addChild(this->progressClip);
	this->addChild(this->slide);
}

CSlider::~CSlider()
{
}

void CSlider::initializePositions()
{
	super::initializePositions();

	this->progressBar->setPosition(Vec2(this->progressBar->getContentSize().width / 2.0f, 0.0f));
	this->progressClip->setPosition(Vec2(-this->progressBar->getContentSize().width / 2.0f, 0.0f));
	this->slide->setPosition(Vec2(this->progress * this->frame->getContentSize().width - this->frame->getContentSize().width / 2, 0));
}

void CSlider::setProgressUpdateCallback(std::function<void(float progress)> callback)
{
	this->progressUpdateEvent = callback;
}

void CSlider::onDrag(MenuSprite* sprite, MouseEvents::MouseEventArgs* args)
{
	Vec2 newPosition = Vec2(args->mouseCoords.x - this->getPositionX(), this->slide->getPosition().y);

	if (newPosition.x < -this->frame->getContentSize().width / 2)
	{
		newPosition.x = -this->frame->getContentSize().width / 2;
	}
	else if (newPosition.x > this->frame->getContentSize().width / 2)
	{
		newPosition.x = this->frame->getContentSize().width / 2;
	}

	this->setProgress((newPosition.x + this->frame->getContentSize().width / 2) / this->frame->getContentSize().width);
	this->slide->setPosition(newPosition);
}

void CSlider::setProgress(float newProgress)
{
	if (newProgress < 0.0f)
	{
		newProgress = 0.0f;
	}
	else if (newProgress > 100.0f)
	{
		newProgress = 100.0f;
	}

	this->progress = newProgress;

	// Update progress bar
	Rect newClippingRegion = this->progressClip->getClippingRegion();
	newClippingRegion.size = Size(this->progressBar->getContentSize().width * this->progress, newClippingRegion.size.height);
	this->progressClip->setClippingRegion(newClippingRegion);

	if (this->progressUpdateEvent != nullptr)
	{
		this->progressUpdateEvent(this->progress);
	}
}
