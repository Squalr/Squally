#include "Slider.h"

Slider* Slider::create()
{
	Slider* slider = new Slider();

	slider->autorelease();

	return slider;
}

Slider::Slider()
{
	this->InitializeListeners();
}

Slider::~Slider()
{
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
