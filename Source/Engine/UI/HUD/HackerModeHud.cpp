#include "HackerModeHud.h"

#include "cocos/2d/CCLayer.h"
#include "cocos/2d/CCNode.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCEventListenerKeyboard.h"

#include "Engine/Events/HackableEvents.h"
#include "Engine/Hackables/HackableObject.h"
#include "Engine/Utils/GameUtils.h"

#include "Menus/HackerMode/RadialMenu.h"

using namespace cocos2d;

HackerModeHud* HackerModeHud::create(std::function<void()> toggleHackermodeCallback)
{
	HackerModeHud* instance = new HackerModeHud(toggleHackermodeCallback);

	instance->autorelease();

	return instance;
}

HackerModeHud::HackerModeHud(std::function<void()> toggleHackermodeCallback)
{
	this->callback = toggleHackermodeCallback;
	this->radialMenu = RadialMenu::create(CC_CALLBACK_0(HackerModeHud::onRadialMenuClose, this));

	this->radialMenu->setVisible(false);

	this->addChild(this->radialMenu);
}

HackerModeHud::~HackerModeHud()
{
}

void HackerModeHud::onEnter()
{
	super::onEnter();
}

void HackerModeHud::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void HackerModeHud::initializeListeners()
{
	super::initializeListeners();

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerCustom* hackableRegisterListener = EventListenerCustom::create(
		HackableEvents::HackableObjectRegisterEvent,
		CC_CALLBACK_1(HackerModeHud::registerHackableObject, this)
	);

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HackerModeHud::onKeyPressed, this);

	this->addEventListener(keyboardListener);
	this->addEventListener(hackableRegisterListener);
}

void HackerModeHud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (!GameUtils::isVisible(this))
	{
		return;
	}

	switch (keyCode)
	{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
		{
			if (this->callback != nullptr)
			{
				this->callback();
			}

			event->stopPropagation();

			break;
		}
		default:
		{
			break;
		}
	}
}

void HackerModeHud::onRadialMenuClose()
{
	GameUtils::focus(this->getParent());
}

void HackerModeHud::registerHackableObject(EventCustom* args)
{
	HackableEvents::HackableObjectRegisterArgs* innerArgs = (HackableEvents::HackableObjectRegisterArgs*)args->getUserData();
	HackableObject* hackableObject = innerArgs->hackableObject;

	if (hackableObject != nullptr)
	{
		// Zac: Disabled, this was causing stupid crashes
		// GameUtils::changeParent(hackableObject->hackButton, this->hackableButtonLayer, true);
	}
}
