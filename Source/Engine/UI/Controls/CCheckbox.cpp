#include "CCheckbox.h"

CCheckbox* CCheckbox::create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback)
{
	CCheckbox* instance = new CCheckbox(uncheckedButton, checkedButton, initialState, callback);

	instance->autorelease();

	return instance;
}

CCheckbox::CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState, std::function<bool(CCheckbox*, bool)> callback)
{
	this->isToggled = initialState;
	this->toggleCallback = callback;
	this->offSwitch = uncheckedButton;
	this->onSwitch = checkedButton;

	this->clickableMenus = new std::vector<MenuSprite*>();

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
	this->getEventDispatcher()->removeEventListenersForTarget(this);
}

void CCheckbox::onToggleClick(MenuSprite* menuSprite)
{
	// Toggle button
	if (menuSprite == offSwitch)
	{
		this->isToggled = true;

	}
	else
	{
		this->isToggled = false;
	}

	// Accept or reject the toggle based on the callback result
	this->isToggled = this->toggleCallback(this, this->isToggled);

	if (this->isToggled)
	{
		this->offSwitch->setVisible(false);
		this->onSwitch->setVisible(true);
	}
	else
	{
		this->offSwitch->setVisible(true);
		this->onSwitch->setVisible(false);
	}
}
