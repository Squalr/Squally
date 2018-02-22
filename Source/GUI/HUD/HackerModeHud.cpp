#include "HackerModeHud.h"

HackerModeHud* HackerModeHud::create()
{
	HackerModeHud* hackerModeHud = new HackerModeHud();

	hackerModeHud->autorelease();

	return hackerModeHud;
}

HackerModeHud::HackerModeHud()
{
	this->hackableObjectsHud = Layer::create();
	this->radialMenu = RadialMenu::create();

	this->radialMenu->setVisible(false);

	this->addChild(this->hackableObjectsHud);
	this->addChild(this->radialMenu);

	this->initializeListeners();
}

HackerModeHud::~HackerModeHud()
{
}

void HackerModeHud::onEnter()
{
	Node::onEnter();

	this->initializePositions();

	this->addChild(Mouse::claimInstance());
}

void HackerModeHud::initializePositions()
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

}

void HackerModeHud::initializeListeners()
{
	EventListenerKeyboard* listener = EventListenerKeyboard::create();

	listener->onKeyPressed = CC_CALLBACK_2(HackerModeHud::onKeyPressed, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(listener, this);
}

void HackerModeHud::onKeyPressed(EventKeyboard::KeyCode keyCode, Event* event)
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

void HackerModeHud::registerHackableObject(HackableObject* hackableObject)
{
	if (hackableObject == nullptr)
	{
		return;
	}

	// Create the hackable button for this hackable object
	MenuSprite* hackableMenuButton = MenuSprite::create(Resources::Menus_HackerModeMenu_HackButton, Resources::Menus_HackerModeMenu_HackButtonHover, Resources::Menus_HackerModeMenu_HackButtonClick);
	hackableMenuButton->setClickCallback(CC_CALLBACK_1(HackableObject::onHackableClick, hackableObject));
	hackableObject->bindHackableButton(hackableMenuButton);

	this->hackableObjectsHud->addChild(hackableMenuButton);
}
