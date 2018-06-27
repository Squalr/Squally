#include "HackerModeHud.h"

HackerModeHud* HackerModeHud::create()
{
	HackerModeHud* instance = new HackerModeHud();

	instance->autorelease();

	return instance;
}

HackerModeHud::HackerModeHud()
{
	this->hackableObjectsHud = Layer::create();
	this->radialMenu = RadialMenu::create(CC_CALLBACK_0(HackerModeHud::onRadialMenuClose, this));

	this->radialMenu->setVisible(false);

	this->addChild(this->hackableObjectsHud);
	this->addChild(this->radialMenu);
	this->addChild(Mouse::create());
}

HackerModeHud::~HackerModeHud()
{
}

void HackerModeHud::onEnter()
{
	Node::onEnter();

	this->initializePositions();
	this->initializeListeners();
}

void HackerModeHud::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

}

void HackerModeHud::initializeListeners()
{
	this->getEventDispatcher()->removeEventListenersForTarget(this);

	EventListenerKeyboard* keyboardListener = EventListenerKeyboard::create();
	EventListenerCustom* hackableRegisterListener = EventListenerCustom::create(
		HackableEvents::HackableObjectRegisterEvent,
		CC_CALLBACK_1(HackerModeHud::registerHackableObject, this)
	);

	keyboardListener->onKeyPressed = CC_CALLBACK_2(HackerModeHud::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(keyboardListener, this);
	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(hackableRegisterListener, this);
}

void HackerModeHud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
{
	if (GameUtils::isFocused(this))
	{
		switch (keyCode)
		{
		case EventKeyboard::KeyCode::KEY_TAB:
		case EventKeyboard::KeyCode::KEY_ESCAPE:
			// This is a little too "all knowing" as this HUD is expecting Level > UILayer > HackerModeHud
			// To avoid this parent of parent bullshit, we need to implement push/pop focus
			GameUtils::focus(this->getParent()->getParent());
			event->stopPropagation();

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

	if (hackableObject == nullptr)
	{
		return;
	}

	// Create the hackable button for this hackable object
	MenuSprite* hackableMenuButton = MenuSprite::create(Resources::Menus_Buttons_CogV2Button, Resources::Menus_Buttons_CogV2ButtonHover, Resources::Menus_Buttons_CogV2ButtonClick);
	hackableMenuButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, hackableObject));
	hackableObject->bindHackableButton(hackableMenuButton);

	this->hackableObjectsHud->addChild(hackableMenuButton);
}
