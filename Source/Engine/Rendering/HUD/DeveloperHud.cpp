#include "DeveloperHud.h"

DeveloperHud* DeveloperHud::create()
{
	DeveloperHud* instance = new DeveloperHud();

	instance->autorelease();

	return instance;
}

DeveloperHud::DeveloperHud()
{
	this->initializeListeners();
}

DeveloperHud::~DeveloperHud()
{
}

void DeveloperHud::onEnter()
{
	Node::onEnter();

	this->initializePositions();
}

void DeveloperHud::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void DeveloperHud::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(DeveloperHud::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void DeveloperHud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (GameUtils::isFocused(this))
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			GameUtils::focus(this->getParent());
			event->stopPropagation();

			break;
		}
	}
}
