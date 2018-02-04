#include "CCheckbox.h"

CCheckbox* CCheckbox::create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<void(bool)> callback)
{
	CCheckbox* checkbox = new CCheckbox(uncheckedButton, checkedButton, initialState, callback);

	checkbox->autorelease();

	return checkbox;
}

CCheckbox::CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<void(bool)> callback)
{
	this->isToggled = initialState;
	this->toggleCallback = callback;
	this->offSwitch = uncheckedButton;
	this->onSwitch = checkedButton;

	this->clickableMenus = new vector<MenuSprite*>();

	this->clickableMenus->push_back(this->offSwitch);
	this->clickableMenus->push_back(this->onSwitch);

	this->offSwitch->setClickCallback(CC_CALLBACK_1(CCheckbox::onToggleClick, this));
	this->onSwitch->setClickCallback(CC_CALLBACK_1(CCheckbox::onToggleClick, this));

	this->addChild(this->offSwitch);
	this->addChild(this->onSwitch);

	if (this->isToggled)
	{
		this->offSwitch->setVisible(false);
	}
	else
	{
		this->onSwitch->setVisible(false);
	}

	this->initializeListeners();
}

CCheckbox::~CCheckbox()
{
}

void CCheckbox::initializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(CCheckbox::onMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void CCheckbox::onToggleClick(MenuSprite* menuSprite)
{
	if (menuSprite == offSwitch)
	{
		this->isToggled = true;

		this->offSwitch->setVisible(false);
		this->onSwitch->setVisible(true);
	}
	else
	{
		this->isToggled = false;

		this->offSwitch->setVisible(true);
		this->onSwitch->setVisible(false);
	}

	this->toggleCallback(this->isToggled);
}

void CCheckbox::onMouseMove(EventMouse* event)
{
	for (std::vector<MenuSprite*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuSprite* menuSprite = *it;
	}
}
