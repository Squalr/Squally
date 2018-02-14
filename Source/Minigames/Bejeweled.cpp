#include "Bejeweled.h"

Bejeweled* Bejeweled::create()
{
	Bejeweled* bejeweled = new Bejeweled();

	bejeweled->autorelease();

	return bejeweled;
}

Bejeweled::Bejeweled()
{
	this->initializePositions();
	this->initializeListeners();
}

Bejeweled::~Bejeweled()
{
}

void Bejeweled::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Bejeweled::initializeListeners()
{
	// this->returnButton->setClickCallback(CC_CALLBACK_1(Bejeweled::onClose, this));

	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Bejeweled::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Bejeweled::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void Bejeweled::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);
	Utils::focus(this->getParent());
}
