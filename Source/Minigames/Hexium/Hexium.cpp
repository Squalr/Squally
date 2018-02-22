#include "Hexium.h"

const std::string BinariumGameStartEvent = "hexium_game_start_event";
const std::string BinariumGameEndEvent = "hexium_game_end_event";

Hexium* Hexium::create()
{
	Hexium* hexium = new Hexium();

	hexium->autorelease();

	return hexium;
}

Hexium::Hexium()
{
	this->initializePositions();
	this->initializeListeners();
}

Hexium::~Hexium()
{
}

void Hexium::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void Hexium::initializeListeners()
{
	// this->returnButton->setClickCallback(CC_CALLBACK_1(Hexium::onClose, this));

	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(Hexium::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void Hexium::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void Hexium::onClose(MenuSprite* menuSprite)
{
	this->setVisible(false);
	Utils::focus(this->getParent());
}
