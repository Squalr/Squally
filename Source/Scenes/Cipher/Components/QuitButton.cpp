#include "QuitButton.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Menus/Return.h"

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
		CipherResources::QuitButton,
		CipherResources::QuitButtonSelected);

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

	this->quitButton->setPosition(Vec2(visibleSize.width / 2.0f + Config::RightColumnCenter, visibleSize.height / 2.0f - 420.0f));
}

void QuitButton::initializeListeners()
{
	super::initializeListeners();

	// this->quitButton->setClickCallback([=](MouseEvents::MouseEventArgs*) { this->onMenuExit();  });
}

void QuitButton::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void QuitButton::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
