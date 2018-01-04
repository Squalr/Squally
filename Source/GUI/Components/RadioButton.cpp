#include "RadioButton.h"

RadioButton* RadioButton::create(int groupIdentifier)
{
	RadioButton* radioButton = new RadioButton(groupIdentifier);

	radioButton->autorelease();

	return radioButton;
}

RadioButton::RadioButton(int groupIdentifier)
{
	this->onCheckCallback = nullptr;
	this->groupId = groupIdentifier;

	this->checked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonSelected, Resources::Menus_OptionsMenu_RadioButtonSelectedHover, Resources::Menus_OptionsMenu_RadioButtonSelectedHover);
	this->unchecked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonEmpty, Resources::Menus_OptionsMenu_RadioButtonHover, Resources::Menus_OptionsMenu_RadioButtonHover);

	this->checked->setClickCallback(CC_CALLBACK_1(RadioButton::onUncheckClick, this));
	this->unchecked->setClickCallback(CC_CALLBACK_1(RadioButton::onCheckClick, this));

	this->isChecked = false;
	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);

	this->initializeListeners();
}

RadioButton::~RadioButton()
{
}

void RadioButton::initializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(this->RadioButtonCheckEvent, CC_CALLBACK_1(RadioButton::onGroupCheck, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
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

void RadioButton::onCheckClick(MenuSprite* menuSprite)
{
	this->check();
}

void RadioButton::onUncheckClick(MenuSprite* menuSprite)
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
