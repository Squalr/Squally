#include "HackerModeHud.h"

HackerModeHud* HackerModeHud::create(std::function<void()> toggleHackermodeCallback)
{
	HackerModeHud* instance = new HackerModeHud(toggleHackermodeCallback);

	instance->autorelease();

	return instance;
}

HackerModeHud::HackerModeHud(std::function<void()> toggleHackermodeCallback)
{
	this->callback = toggleHackermodeCallback;
	this->hackableButtonLayer = Node::create();
	this->radialMenu = RadialMenu::create(CC_CALLBACK_0(HackerModeHud::onRadialMenuClose, this));

	this->radialMenu->setVisible(false);

	this->addChild(this->hackableButtonLayer);
	this->addChild(this->radialMenu);
	this->addChild(Mouse::create());
}

HackerModeHud::~HackerModeHud()
{
}

void HackerModeHud::onEnter()
{
	Hud::onEnter();
}

void HackerModeHud::initializePositions()
{
	Hud::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void HackerModeHud::initializeListeners()
{
	Hud::initializeListeners();

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
	if (GameUtils::isFocused(this))
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			if (this->callback != nullptr)
			{
				this->callback();
			}

			event->stopPropagation();

			break;
		default:
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
		GameUtils::changeParent(hackableObject->hackButton, this->hackableButtonLayer, true);
	}
}
