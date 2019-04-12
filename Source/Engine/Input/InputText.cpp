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

InputText* InputText::create(Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize, bool unfuck)
{
	InputText* instance = new InputText(minimumInputSize, fontStyle, fontSize, unfuck);

	instance->autorelease();

	return instance;
}

InputText::InputText(Size minimumInputSize, LocalizedLabel::FontStyle fontStyle, LocalizedLabel::FontSize fontSize, bool unfuck)
{
	this->minimumInputSize = minimumInputSize;
	this->unfuck = unfuck;
	this->labelText = ConstantString::create();
	this->inputLabel = LocalizedLabel::create(fontStyle, fontSize, this->labelText);
	this->hitBox = ClickableNode::create();
	this->initCoords = Vec2::ZERO;
	this->stringCache = this->labelText->getString();
	this->stringChangeCallback = nullptr;

	this->inputLabel->setAnchorPoint(Vec2::ZERO);
	this->hitBox->setAnchorPoint(Vec2::ZERO);
	this->hitBox->setClickSound("");
	this->hitBox->setMouseOverSound("");
	this->initWithPlaceHolder(this->inputLabel->getString(), this->inputLabel->getFont(), this->inputLabel->getFontSize());
	this->inputLabel->setVisible(false);

	this->setDimensions(minimumInputSize.width, minimumInputSize.height);

	this->addChild(this->inputLabel);
	this->addChild(this->hitBox);
}

void InputText::onEnter()
{
	super::onEnter();

	this->hitBox->setMouseClickCallback([=](MouseEvents::MouseEventArgs*)
	{
		this->attachWithIME();
	});

	this->initializePositions();
}

void InputText::initializePositions()
{
	Size newSize = this->resize();
	Vec2 offset = Vec2(newSize.width / 2.0f, newSize.height / 2.0f);

	this->labelText->setPosition(offset);
	this->hitBox->setPosition(offset);

	this->initCoords = this->getPosition();
}

cocos2d::Size InputText::resize()
{
	Size newSize = Size(std::max(this->minimumInputSize.width, this->getContentSize().width), std::max(this->minimumInputSize.height, this->getContentSize().height));
	
	this->hitBox->setContentSize(newSize);

	return newSize;
}

void InputText::update(float dt)
{
	super::update(dt);

	if (this->getString() != this->stringCache)
	{
		this->stringCache = this->getString();

		if (this->stringChangeCallback != nullptr)
		{
			this->stringChangeCallback(this->stringCache);
		}
	}
}

void InputText::setStringChangeCallback(std::function<void(std::string)> stringChangeCallback)
{
	this->stringChangeCallback = stringChangeCallback;
}

void InputText::setString(const std::string& label)
{
	super::setString(label);

	this->labelText->setString(label);

	Size newSize = this->resize();

	if (this->unfuck)
	{
		if (this->getAttachWithIME())
		{
			this->setPositionY(this->initCoords.y + newSize.height / 2.0f);
		}
		else
		{
			this->setPositionY(this->initCoords.y);
		}
		
	}
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
	return this->hitBox;
}
