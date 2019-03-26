#include "SmartAsciiLabel.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/ConstantString.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/Utils/HackUtils.h"
#include "Scenes/Cipher/Components/Letters/AsciiLetter.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Ascii.h"

using namespace cocos2d;


SmartAsciiLabel* SmartAsciiLabel::create()
{
	return SmartAsciiLabel::create((unsigned char)(0));
}

SmartAsciiLabel* SmartAsciiLabel::create(unsigned char charValue)
{
	SmartAsciiLabel* instance = new SmartAsciiLabel(charValue);

	instance->autorelease();

	return instance;
}

SmartAsciiLabel::SmartAsciiLabel(unsigned char charValue)
{
	this->charValue = charValue;
	this->asciiLetterLabel = AsciiLetter::create();
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H3, this->displayValue);

	this->displayDataType = CipherEvents::DisplayDataType::Ascii;

	this->addChild(this->asciiLetterLabel);
	this->addChild(this->displayLabel);
}

SmartAsciiLabel::~SmartAsciiLabel()
{
}

void SmartAsciiLabel::onEnter()
{
	super::onEnter();

	this->loadDisplayValue();
}

void SmartAsciiLabel::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void SmartAsciiLabel::initializeListeners()
{
	super::initializeListeners();

	this->addEventListenerIgnorePause(EventListenerCustom::create(CipherEvents::EventChangeDisplayDataType, [&](EventCustom* eventCustom)
	{
		CipherEvents::CipherChangeDisplayDataTypeArgs* args = static_cast<CipherEvents::CipherChangeDisplayDataTypeArgs*>(eventCustom->getUserData());

		if (args != nullptr)
		{
			this->displayDataType = args->displayDataType;

			this->loadDisplayValue();
		}
	}));
}

void SmartAsciiLabel::setValue(unsigned char value)
{
	this->charValue = value;
}

void SmartAsciiLabel::loadDisplayValue()
{
	this->asciiLetterLabel->setVisible(false);
	this->displayLabel->setVisible(false);

	switch(this->displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->asciiLetterLabel->loadLetter(this->charValue);
			this->asciiLetterLabel->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(HackUtils::toBinary8(int(this->charValue)));
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(std::to_string(int(this->charValue)));
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(HackUtils::toHex(int(this->charValue)));
			break;
		}
	}
}
