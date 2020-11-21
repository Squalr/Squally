#include "AsciiButton.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Events/CipherEvents.h"
#include "Scenes/Cipher/CipherConfig.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

AsciiButton* AsciiButton::create()
{
	AsciiButton* instance = new AsciiButton();

	instance->autorelease();

	return instance;
}

AsciiButton::AsciiButton()
{
	LocalizedLabel*	asciiLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Ascii::create());
	LocalizedLabel*	asciiLabelHover = asciiLabel->clone();

	asciiLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	asciiLabel->enableGlow(Color4B::BLACK);

	asciiLabelHover->setColor(Color3B::YELLOW);
	asciiLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	asciiLabelHover->enableGlow(Color4B::ORANGE);

	this->asciiButton = ClickableTextNode::create(
		asciiLabel,
		asciiLabelHover,
		CipherResources::Buttons_AsciiTableButton,
		CipherResources::Buttons_AsciiTableButtonSelected);

	this->addChild(this->asciiButton);
}

AsciiButton::~AsciiButton()
{
}

void AsciiButton::onEnter()
{
	super::onEnter();
}

void AsciiButton::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->asciiButton->setPosition(Vec2(visibleSize.width / 2.0f + CipherConfig::LeftColumnCenter + 448.0f, visibleSize.height / 2.0f + 420.0f));
}

void AsciiButton::initializeListeners()
{
	super::initializeListeners();

	this->asciiButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CipherEvents::TriggerOpenAsciiTable(CipherEvents::CipherOpenAsciiTableArgs(nullptr));
	});
}

void AsciiButton::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Neutral:
		{
			this->asciiButton->enableInteraction();
			break;
		}
		default:
		{
			this->asciiButton->disableInteraction();
			break;
		}
	}
}
