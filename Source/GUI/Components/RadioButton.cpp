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

	this->checked->SetClickCallback(CC_CALLBACK_1(RadioButton::OnUncheck, this));
	this->unchecked->SetClickCallback(CC_CALLBACK_1(RadioButton::OnCheck, this));

	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);

	this->InitializeListeners();
}

RadioButton::~RadioButton()
{
}

void RadioButton::InitializeListeners()
{
	EventListenerCustom* customListener = EventListenerCustom::create(this->RadioButtonCheckEvent, CC_CALLBACK_1(RadioButton::OnGroupCheck, this));

	this->getEventDispatcher()->addEventListenerWithSceneGraphPriority(customListener, this);
}

void RadioButton::SetCheckCallback(std::function<void(RadioButton*)> callback)
{
	this->onCheckCallback = callback;
}

void RadioButton::OnGroupCheck(EventCustom* event)
{
	int* eventGroupId = static_cast<int*>(event->getUserData());

	if (*eventGroupId == this->groupId)
	{
		this->UncheckSilent();
	}
}


void RadioButton::OnCheck(MenuSprite* menuSprite)
{
	this->Check();
}

void RadioButton::OnUncheck(MenuSprite* menuSprite)
{
	this->Uncheck();
}

void RadioButton::Check()
{
	this->getEventDispatcher()->dispatchCustomEvent(this->RadioButtonCheckEvent, &this->groupId);

	this->checked->setVisible(true);
	this->unchecked->setVisible(false);

	if (this->onCheckCallback != nullptr)
	{
		this->onCheckCallback(this);
	}
}

void RadioButton::Uncheck()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);
}

void RadioButton::UncheckSilent()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);
}
