#include "DeveloperHud.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Maps/SerializableMap.h"
#include "Engine/UI/Controls/MenuSprite.h"
#include "Engine/UI/Mouse.h"
#include "Engine/Utils/GameUtils.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

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
	this->saveButton = MenuSprite::create(UIResources::Menus_Buttons_DownloadV2Button, UIResources::Menus_Buttons_DownloadV2ButtonHover);

	this->layerSelectionBackground->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->layerSelectionBackground);
	this->addChild(this->saveButton);
}

DeveloperHud::~DeveloperHud()
{
}

void DeveloperHud::loadMap(SerializableMap* serializableMapInit)
{
	this->serializableMap = serializableMapInit;
}

void DeveloperHud::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->saveButton->setPosition(Vec2(visibleSize.width - this->saveButton->getContentSize().width, visibleSize.height - this->saveButton->getContentSize().height));
}

void DeveloperHud::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();

	keyboardListener->onKeyPressed = CC_CALLBACK_2(DeveloperHud::onKeyPressed, this);

	this->saveButton->setClickCallback(CC_CALLBACK_1(DeveloperHud::onSaveClick, this));

	this->addEventListener(keyboardListener);
}

void DeveloperHud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isFocused(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			GameUtils::focus(this->getParent());
			event->stopPropagation();

			break;
		}
	}
}

void DeveloperHud::onSaveClick(MenuSprite* menuSprite)
{
	this->serializableMap->serialize();
}
