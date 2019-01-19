#include "InputText.h"

#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Resources/UIResources.h"

using namespace cocos2d;
using namespace cocos2d::ui;


InputText* InputText::create(LocalizedLabel* referenceLabel)
{
	InputText* instance = new InputText(referenceLabel);

	instance->autorelease();

	return instance;
}

InputText::InputText(LocalizedLabel* referenceLabel)
{
	this->referenceLabel = referenceLabel;
	this->hitbox = ClickableNode::create(UIResources::EmptyImage, UIResources::EmptyImage);

	this->initWithPlaceHolder(referenceLabel->getString(), referenceLabel->getFont(), referenceLabel->getFontSize());

	this->addChild(this->referenceLabel);
	this->addChild(this->hitbox);
}

void InputText::onEnter()
{
	super::onEnter();

	this->scheduleUpdate();

	this->hitbox->setClickCallback([=](ClickableNode*, MouseEvents::MouseEventArgs*)
	{
		this->attachWithIME();
	});
}

void InputText::update(float dt)
{
	super::update(dt);

	if (!this->hitbox->getContentSize().equals(this->getContentSize()))
	{
		this->hitbox->setContentSize(this->getContentSize());
	}
}

std::string InputText::getFont()
{
	return this->referenceLabel->getFont();
}

float InputText::getFontSize()
{
	return this->referenceLabel->getFontSize();
}
