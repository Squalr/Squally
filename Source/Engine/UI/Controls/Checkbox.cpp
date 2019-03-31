#include "Checkbox.h"

#include "cocos/base/ccMacros.h"

#include "Engine/Input/ClickableNode.h"

using namespace cocos2d;

Checkbox* Checkbox::create(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
		std::function<bool(Checkbox*, bool)> callback)
{
	Checkbox* instance = new Checkbox(uncheckedButton, checkedButton, initialState, callback);

	instance->autorelease();

	return instance;
}

Checkbox::Checkbox(ClickableNode* uncheckedButton, ClickableNode* checkedButton, bool initialState,
		std::function<bool(Checkbox*, bool)> callback)
{
	this->isToggled = initialState;
	this->toggleCallback = callback;
	this->offSwitch = uncheckedButton;
	this->onSwitch = checkedButton;

	this->clickableMenus = new std::vector<ClickableNode*>();

	this->clickableMenus->push_back(this->offSwitch);
	this->clickableMenus->push_back(this->onSwitch);

	this->offSwitch->setMouseClickCallback(CC_CALLBACK_0(Checkbox::onToggle, this));
	this->onSwitch->setMouseClickCallback(CC_CALLBACK_0(Checkbox::onUntoggle, this));

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

Checkbox::~Checkbox()
{
}

void Checkbox::setCallback(std::function<bool(Checkbox*, bool)> callback)
{
	this->toggleCallback = callback;
}

void Checkbox::setToggled(bool isToggled)
{
	this->isToggled = isToggled;

	this->updateVisuals();
}

bool Checkbox::getToggled()
{
	return this->isToggled;
}

void Checkbox::onToggle()
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

void Checkbox::onUntoggle()
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

void Checkbox::updateVisuals()
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
