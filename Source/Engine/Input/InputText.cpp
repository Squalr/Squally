#include "InputText.h"

#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/ui/UIRichText.h"
#include "cocos/ui/UIScrollView.h"
#include "cocos/ui/UITextField.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"

#include "Strings/Generics/Constant.h"

using namespace cocos2d;
using namespace cocos2d::ui;


InputText* InputText::create(Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize)
{
	InputText* instance = new InputText(minimumInputSize, fontStyle, fontSize);

	instance->autorelease();

	return instance;
}

InputText::InputText(Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize)
{
	this->minimumInputSize = minimumInputSize;
	this->labelText = ConstantString::create();
	this->inputLabel = LocalizedLabel::create(fontStyle, fontSize, this->labelText);
	this->hitbox = ClickableNode::create();

	this->inputLabel->setAnchorPoint(Vec2::ZERO);
	this->hitbox->setAnchorPoint(Vec2::ZERO);
	this->hitbox->setClickSound("");
	this->hitbox->setMouseOverSound("");
	this->initWithPlaceHolder(this->inputLabel->getString(), this->inputLabel->getFont(), this->inputLabel->getFontSize());
	this->inputLabel->setVisible(false);

	this->setDimensions(minimumInputSize.width, minimumInputSize.height);

	this->addChild(this->inputLabel);
	this->addChild(this->hitbox);
}

void InputText::onEnter()
{
	super::onEnter();

	this->hitbox->setClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->attachWithIME();
	});

	this->initializePositions();
}

void InputText::initializePositions()
{
	Size newSize = Size(std::max(this->minimumInputSize.width, this->getContentSize().width), std::max(this->minimumInputSize.height, this->getContentSize().height));
	Vec2 offset = Vec2(newSize.width / 2.0f, newSize.height / 2.0f);

	this->hitbox->setContentSize(newSize);
	this->labelText->setPosition(offset);
	this->hitbox->setPosition(offset);
}

void InputText::setString(const std::string& label)
{
	super::setString(label);

	this->labelText->setString(label);
	this->initializePositions();
}

std::string InputText::getFont()
{
	return this->inputLabel->getFont();
}

float InputText::getFontSize()
{
	return this->inputLabel->getFontSize();
}

ClickableNode* InputText::getHitbox()
{
	return this->hitbox;
}
