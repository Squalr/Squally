#include "ToggleButton.h"

ToggleButton* ToggleButton::create()
{
	ToggleButton* toggleButton = new ToggleButton();

	toggleButton->autorelease();

	return toggleButton;
}

ToggleButton::ToggleButton()
{
	this->offSwitch = MenuSprite::create(Resources::Menus_OptionsMenu_ToggleButtonOff, Resources::Menus_OptionsMenu_ToggleButtonOffHover, Resources::Menus_OptionsMenu_ToggleButtonOffClick);
	this->onSwitch = MenuSprite::create(Resources::Menus_OptionsMenu_ToggleButtonOn, Resources::Menus_OptionsMenu_ToggleButtonOnHover, Resources::Menus_OptionsMenu_ToggleButtonOnClick);

	this->addChild(this->offSwitch);
	this->addChild(this->onSwitch);

	this->InitializeListeners();
}

ToggleButton::~ToggleButton()
{
}

void ToggleButton::InitializePositions()
{
	this->offSwitch->setPosition(Vec2(0, 0));
	this->onSwitch->setPosition(Vec2(0, 0));
}

void ToggleButton::InitializeListeners()
{
}
