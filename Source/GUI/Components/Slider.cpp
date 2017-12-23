#include "Slider.h"

Slider* Slider::create(float progress)
{
	Slider* slider = new Slider(progress);

	slider->autorelease();

	return slider;
}

Slider::Slider(float progress)
{
	this->progress = progress;
	this->frame = Sprite::create(Resources::Menus_OptionsMenu_SliderFrame);
	this->progressBar = Sprite::create(Resources::Menus_OptionsMenu_SliderFill);
	this->slide = MenuSprite::create(Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide, Resources::Menus_OptionsMenu_Slide);

	this->addChild(this->frame);
	this->addChild(this->progressBar);
	this->addChild(this->slide);

	this->InitializeListeners();
}

Slider::~Slider()
{
}

void Slider::InitializePositions()
{
	this->slide->setPosition(Vec2(0, 0));
}

void Slider::InitializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(Slider::OnMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void Slider::OnMouseMove(EventMouse* event)
{
}
