#include "CCheckbox.h"

#include "cocos/base/ccMacros.h"

#include "Engine/UI/Controls/MenuSprite.h"

using namespace cocos2d;

CCheckbox* CCheckbox::create(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState,
		std::function<bool(CCheckbox*, bool)> callback)
{
	CCheckbox* instance = new CCheckbox(uncheckedButton, checkedButton, initialState, callback);

	instance->autorelease();

	return instance;
}

CCheckbox::CCheckbox(MenuSprite* uncheckedButton, MenuSprite* checkedButton, bool initialState,
		std::function<bool(CCheckbox*, bool)> callback)
{
	this->isToggled = initialState;
	this->toggleCallback = callback;
	this->offSwitch = uncheckedButton;
	this->onSwitch = checkedButton;

	this->clickableMenus = new std::vector<MenuSprite*>();

	this->clickableMenus->push_back(this->offSwitch);
	this->clickableMenus->push_back(this->onSwitch);

	this->offSwitch->setClickCallback(CC_CALLBACK_0(CCheckbox::onToggle, this));
	this->onSwitch->setClickCallback(CC_CALLBACK_0(CCheckbox::onUntoggle, this));

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
}

CCheckbox::~CCheckbox()
{
}

void CCheckbox::setCallback(std::function<bool(CCheckbox*, bool)> callback)
{
	this->toggleCallback = callback;
}

void CCheckbox::setToggled(bool isToggled)
{
	this->isToggled = isToggled;

	this->updateVisuals();
}

bool CCheckbox::getToggled()
{
	return this->isToggled;
}

void CCheckbox::onToggle()
{
	if (this->toggleCallback != nullptr)
	{
		// Accept or reject the toggle based on the callback result
		this->isToggled = this->toggleCallback(this, true);
	}
	else
	{
		this->isToggled = true;
	}

	this->updateVisuals();
}

void CCheckbox::onUntoggle()
{
	if (this->toggleCallback != nullptr)
	{
		// Accept or reject the toggle based on the callback result
		this->isToggled = this->toggleCallback(this, false);
	}
	else
	{
		this->isToggled = false;
	}

	this->updateVisuals();
}

void CCheckbox::updateVisuals()
{
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
