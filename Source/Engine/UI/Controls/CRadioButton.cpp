#include "CRadioButton.h"

CRadioButton* CRadioButton::create(int groupIdentifier)
{
	CRadioButton* instance = new CRadioButton(groupIdentifier);

	instance->autorelease();

	return instance;
}

CRadioButton::CRadioButton(int groupIdentifier)
{
	this->onCheckCallback = nullptr;
	this->groupId = groupIdentifier;

	this->checked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonSelected, Resources::Menus_OptionsMenu_RadioButtonSelectedHover);
	this->unchecked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonEmpty, Resources::Menus_OptionsMenu_RadioButtonHover);

	this->checked->setClickCallback(CC_CALLBACK_1(CRadioButton::onUncheckClick, this));
	this->unchecked->setClickCallback(CC_CALLBACK_1(CRadioButton::onCheckClick, this));

	this->isChecked = false;
	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);
}

CRadioButton::~CRadioButton()
{
}

void CRadioButton::initializeListeners()
{
	SmartNode::initializeListeners();

	EventListenerCustom* customListener = EventListenerCustom::create(this->RadioButtonCheckEvent, CC_CALLBACK_1(CRadioButton::onGroupCheck, this));

	this->addEventListener(customListener);
}

void CRadioButton::setCheckCallback(std::function<void(CRadioButton*)> callback)
{
	this->onCheckCallback = callback;
}

void CRadioButton::onGroupCheck(EventCustom* event)
{
	int* eventGroupId = static_cast<int*>(event->getUserData());

	if (*eventGroupId == this->groupId)
	{
		this->uncheck();
	}
}

void CRadioButton::onCheckClick(MenuSprite* menuSprite)
{
	this->check();
}

void CRadioButton::onUncheckClick(MenuSprite* menuSprite)
{
	// Actually just do nothing because we should always have one radio button selected
	// this->uncheck();
}

void CRadioButton::check()
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

void CRadioButton::uncheck()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);

	this->isChecked = false;
}
