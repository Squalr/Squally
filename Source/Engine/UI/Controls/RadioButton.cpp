#include "RadioButton.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventDispatcher.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Engine/Input/ClickableNode.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

RadioButton* RadioButton::create(int groupIdentifier)
{
	RadioButton* instance = new RadioButton(groupIdentifier);

	instance->autorelease();

	return instance;
}

RadioButton::RadioButton(int groupIdentifier)
{
	this->onCheckCallback = nullptr;
	this->groupId = groupIdentifier;

	this->checked = ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonSelected, UIResources::Menus_OptionsMenu_RadioButtonSelectedHover);
	this->unchecked = ClickableNode::create(UIResources::Menus_OptionsMenu_RadioButtonEmpty, UIResources::Menus_OptionsMenu_RadioButtonHover);

	this->checked->setClickCallback(CC_CALLBACK_1(RadioButton::onUncheckClick, this));
	this->unchecked->setClickCallback(CC_CALLBACK_1(RadioButton::onCheckClick, this));

	this->isChecked = false;
	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);
}

RadioButton::~RadioButton()
{
}

void RadioButton::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* customListener = EventListenerCustom::create(this->RadioButtonCheckEvent, CC_CALLBACK_1(RadioButton::onGroupCheck, this));

	this->addEventListener(customListener);
}

void RadioButton::setCheckCallback(std::function<void(RadioButton*)> callback)
{
	this->onCheckCallback = callback;
}

void RadioButton::onGroupCheck(EventCustom* event)
{
	int* eventGroupId = static_cast<int*>(event->getUserData());

	if (*eventGroupId == this->groupId)
	{
		this->uncheck();
	}
}

void RadioButton::onCheckClick(ClickableNode* menuSprite)
{
	this->check();
}

void RadioButton::onUncheckClick(ClickableNode* menuSprite)
{
	// Actually just do nothing because we should always have one radio button selected
	// this->uncheck();
}

void RadioButton::check()
{
	if (!this->isChecked)
	{
		this->getEventDispatcher()->dispatchCustomEvent(this->RadioButtonCheckEvent, &this->groupId);

		this->checked->setVisible(true);
		this->unchecked->setVisible(false);

		if (this->onCheckCallback != nullptr)
		{
			this->onCheckCallback(this);
		}

		this->isChecked = true;
	}
}

void RadioButton::uncheck()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);

	this->isChecked = false;
}
