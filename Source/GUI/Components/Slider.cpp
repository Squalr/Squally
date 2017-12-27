#include "Slider.h"

Slider* Slider::create(float progress)
{
	Slider* slider = new Slider(progress);

	slider->autorelease();

	return slider;
}

Slider::Slider(float progress)
{
	this->progressUpdateEvent = nullptr;

	this->frame = Sprite::create(Resources::Menus_OptionsMenu_SliderFrame);
	this->progressBar = Sprite::create(Resources::Menus_OptionsMenu_SliderFill);
	this->progressClip = ClippingRectangleNode::create(Rect(0, -32, this->progressBar->getContentSize().width, 64));
	this->slide = MenuSprite::create(Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide);

	this->setCascadeOpacityEnabled(true);
	this->progressClip->setCascadeOpacityEnabled(true);
	this->setProgress(progress);

	this->slide->setMouseDragCallback(CC_CALLBACK_2(Slider::onDrag, this));

	this->progressBar->setAnchorPoint(Vec2(0.0f, 0.5f));
	this->progressClip->addChild(this->progressBar);

	this->addChild(this->frame);
	this->addChild(this->progressClip);
	this->addChild(this->slide);

	this->initializePositions();
}

Slider::~Slider()
{
}

void Slider::initializePositions()
{
	this->progressClip->setPosition(Vec2(-this->progressBar->getContentSize().width / 2, 0));
	this->slide->setPosition(Vec2(this->progress * this->frame->getContentSize().width - this->frame->getContentSize().width / 2, 0));
}

void Slider::setProgressUpdateCallback(std::function<void(float progress)> callback)
{
	this->progressUpdateEvent = callback;
}

void Slider::onDrag(MenuSprite* sprite, EventMouse* args)
{
	Vec2 newPosition = Vec2(args->getCursorX() - this->getPositionX(), this->slide->getPosition().y);

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

void Slider::setProgress(float newProgress)
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
