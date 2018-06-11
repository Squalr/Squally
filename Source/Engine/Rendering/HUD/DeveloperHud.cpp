#include "DeveloperHud.h"

const Color4B DeveloperHud::menuColor = Color4B(54.0f, 112.0f, 106.0f, 196.0f);

DeveloperHud* DeveloperHud::create()
{
	DeveloperHud* instance = new DeveloperHud();

	instance->autorelease();

	return instance;
}

DeveloperHud::DeveloperHud()
{
	this->layerSelectionBackground = LayerColor::create(menuColor, 320.0f, 1280.0f);

	this->layerSelectionBackground->setAnchorPoint(Vec2(0.0f, 1.0f));
	
	this->addChild(this->layerSelectionBackground);
}

DeveloperHud::~DeveloperHud()
{
}

void DeveloperHud::loadLevel(SerializableMap* map)
{
	this->levelMap = map;
}

void DeveloperHud::onEnter()
{
	Node::onEnter();

	this->initializeListeners();
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
