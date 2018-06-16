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
	this->saveButton = MenuSprite::create(Resources::Menus_DeveloperMenu_SaveButton, Resources::Menus_DeveloperMenu_SaveButtonHover, Resources::Menus_DeveloperMenu_SaveButtonClick);

	this->layerSelectionBackground->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->layerSelectionBackground);
	this->addChild(this->saveButton);
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

	this->saveButton->setPosition(Vec2(visibleSize.width - this->saveButton->getContentSize().width, visibleSize.height - this->saveButton->getContentSize().height));
}

void DeveloperHud::initializeListeners()
{
	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(DeveloperHud::onKeyPressed, this);

	this->saveButton->setClickCallback(CC_CALLBACK_1(DeveloperHud::onSaveClick, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
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

void DeveloperHud::onSaveClick(MenuSprite* menuSprite)
{
	this->levelMap->serialize();
}
