#include "Binarium.h"

Binarium* Binarium::create()
{
	Binarium* binarium = new Binarium();

	binarium->autorelease();

	return binarium;
}

Binarium::Binarium()
{
	this->initializePositions();
	this->initializeListeners();
}

Binarium::~Binarium()
{
}

void Binarium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Binarium::initializeListeners()
{
	// this->returnButton->setClickCallback(CC_CALLBACK_1(Binarium::onClose, this));

	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Binarium::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Binarium::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!this->isVisible())
	{
		return;
	}

	switch (keyCode)
	{
	case EventKeyboard::KeyCode::KEY_ESCAPE:
		this->setVisible(false);
		Utils::focus(this->getParent());
		event->stopPropagation();
		break;
	}
}

void Binarium::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);
	Utils::focus(this->getParent());
}
