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
	this->progress = progress;
	this->frame = Sprite::create(Resources::Menus_OptionsMenu_SliderFrame);
	this->progressBar = Sprite::create(Resources::Menus_OptionsMenu_SliderFill);
	this->slide = MenuSprite::create(Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide);

	this->slide->SetMouseDragCallback(CC_CALLBACK_2(Slider::OnDrag, this));

	this->addChild(this->frame);
	this->addChild(this->progressBar);
	this->addChild(this->slide);

	this->InitializePositions();
}

Slider::~Slider()
{
}

void Slider::InitializePositions()
{
	this->slide->setPosition(Vec2(this->progress * this->frame->getContentSize().width - this->frame->getContentSize().width / 2, 0));
}

void Slider::SetProgressUpdateCallback(std::function<void(float progress)> callback)
{
	this->progressUpdateEvent = callback;
}

void Slider::OnDrag(MenuSprite* sprite, EventMouse* args)
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

	this->SetProgress((newPosition.x + this->frame->getContentSize().width / 2) / this->frame->getContentSize().width);
	this->slide->setPosition(newPosition);
}

void Slider::SetProgress(float newProgress)
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

	if (this->progressUpdateEvent != nullptr)
	{
		this->progressUpdateEvent(this->progress);
	}
}
