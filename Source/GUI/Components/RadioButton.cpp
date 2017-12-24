#include "RadioButton.h"

RadioButton* RadioButton::create(RadioButtonGroup* group)
{
	RadioButton* radioButton = new RadioButton(group);

	radioButton->autorelease();

	return radioButton;
}

RadioButton::RadioButton(RadioButtonGroup* group)
{
	this->checked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonSelected, Resources::Menus_OptionsMenu_RadioButtonSelectedHover, Resources::Menus_OptionsMenu_RadioButtonSelectedHover);
	this->unchecked = MenuSprite::create(Resources::Menus_OptionsMenu_RadioButtonEmpty, Resources::Menus_OptionsMenu_RadioButtonHover, Resources::Menus_OptionsMenu_RadioButtonHover);

	this->checked->SetClickCallback(CC_CALLBACK_1(RadioButton::OnUncheck, this));
	this->unchecked->SetClickCallback(CC_CALLBACK_1(RadioButton::OnCheck, this));

	this->checked->setVisible(false);

	this->addChild(this->unchecked);
	this->addChild(this->checked);
}

RadioButton::~RadioButton()
{
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
	this->checked->setVisible(true);
	this->unchecked->setVisible(false);
}

void RadioButton::Uncheck()
{
	this->checked->setVisible(false);
	this->unchecked->setVisible(true);
}
