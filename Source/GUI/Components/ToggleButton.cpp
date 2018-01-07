#include "ToggleButton.h"

ToggleButton* ToggleButton::create(bool initialState, std::function<void(bool)> callback)
{
	ToggleButton* toggleButton = new ToggleButton(initialState, callback);

	toggleButton->autorelease();

	return toggleButton;
}

ToggleButton::ToggleButton(bool initialState, std::function<void(bool)> callback)
{
	this->isToggled = initialState;
	this->toggleCallback = callback;
	this->offSwitch = MenuSprite::create(Sprite::create(Resources::Menus_OptionsMenu_ToggleButtonOff), Resources::Menus_OptionsMenu_ToggleButtonOffHover, Resources::Menus_OptionsMenu_ToggleButtonOffClick);
	this->onSwitch = MenuSprite::create(Sprite::create(Resources::Menus_OptionsMenu_ToggleButtonOn), Resources::Menus_OptionsMenu_ToggleButtonOnHover, Resources::Menus_OptionsMenu_ToggleButtonOnClick);

	this->clickableMenus = new vector<MenuSprite*>();

	this->clickableMenus->push_back(this->offSwitch);
	this->clickableMenus->push_back(this->onSwitch);

	this->offSwitch->setClickCallback(CC_CALLBACK_1(ToggleButton::onToggleClick, this));
	this->onSwitch->setClickCallback(CC_CALLBACK_1(ToggleButton::onToggleClick, this));

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

ToggleButton::~ToggleButton()
{
}

void ToggleButton::initializeListeners()
{
	EventListenerMouse* mouseListener = EventListenerMouse::create();

	mouseListener->onMouseMove = CC_CALLBACK_1(ToggleButton::onMouseMove, this);

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(mouseListener, this);
}

void ToggleButton::onToggleClick(MenuSprite* menuSprite)
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

void ToggleButton::onMouseMove(EventMouse* event)
{
	for (std::vector<MenuSprite*>::iterator it = this->clickableMenus->begin(); it != this->clickableMenus->end(); ++it)
	{
		MenuSprite* menuSprite = *it;
	}
}
