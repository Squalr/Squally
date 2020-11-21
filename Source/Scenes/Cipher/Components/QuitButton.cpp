#include "QuitButton.h"

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

QuitButton* QuitButton::create()
{
	QuitButton* instance = new QuitButton();

	instance->autorelease();

	return instance;
}

QuitButton::QuitButton()
{
	LocalizedLabel*	quitLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Return::create());
	LocalizedLabel*	quitLabelHover = quitLabel->clone();

	quitLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabel->enableGlow(Color4B::BLACK);

	quitLabelHover->setColor(Color3B::YELLOW);
	quitLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	quitLabelHover->enableGlow(Color4B::ORANGE);

	this->quitButton = ClickableTextNode::create(
		quitLabel,
		quitLabelHover,
		CipherResources::Buttons_QuitButton,
		CipherResources::Buttons_QuitButtonSelected);

	this->addChild(this->quitButton);
}

QuitButton::~QuitButton()
{
}

void QuitButton::onEnter()
{
	super::onEnter();
}

void QuitButton::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->quitButton->setPosition(Vec2(visibleSize.width / 2.0f + CipherConfig::RightColumnCenter, visibleSize.height / 2.0f - 444.0f));
}

void QuitButton::initializeListeners()
{
	super::initializeListeners();

	this->quitButton->setMouseClickCallback([=](InputEvents::MouseEventArgs*)
	{
		CipherEvents::TriggerExitCipher(CipherEvents::CipherExitArgs(false));
	});
}

void QuitButton::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Neutral:
		{
			this->quitButton->enableInteraction();
			break;
		}
		default:
		{
			this->quitButton->disableInteraction();
			break;
		}
	}
}
