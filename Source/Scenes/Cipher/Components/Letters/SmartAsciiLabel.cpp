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
	SmartAsciiLabel* instance = new SmartAsciiLabel();

	instance->autorelease();

	return instance;
}

SmartAsciiLabel::SmartAsciiLabel()
{
	this->asciiLetterLabel = AsciiLetter::create();
	this->displayValue = ConstantString::create();
	this->displayLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Coding, LocalizedLabel::FontSize::H1, this->displayValue);

	this->displayLabel->enableOutline(Color4B::BLACK, 3);

	this->addChild(this->asciiLetterLabel);
	this->addChild(this->displayLabel);
}

SmartAsciiLabel::~SmartAsciiLabel()
{
}

void SmartAsciiLabel::onEnter()
{
	super::onEnter();
}

void SmartAsciiLabel::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();
}

void SmartAsciiLabel::initializeListeners()
{
	super::initializeListeners();
}

void SmartAsciiLabel::loadDisplayValue(unsigned char charValue, CipherEvents::DisplayDataType displayDataType)
{
	this->asciiLetterLabel->setVisible(false);
	this->displayLabel->setVisible(false);

	switch(displayDataType)
	{
		default:
		case CipherEvents::DisplayDataType::Ascii:
		{
			this->asciiLetterLabel->loadLetter(charValue);
			this->asciiLetterLabel->setVisible(true);
			break;
		}
		case CipherEvents::DisplayDataType::Bin:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(HackUtils::toBinary8(int(charValue)));
			break;
		}
		case CipherEvents::DisplayDataType::Dec:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(std::to_string(int(charValue)));
			break;
		}
		case CipherEvents::DisplayDataType::Hex:
		{
			this->displayLabel->setVisible(true);
			this->displayValue->setString(HackUtils::toHex(int(charValue)));
			break;
		}
	}
}
