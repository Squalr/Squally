#include "ExecuteButton.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Cipher/Execute.h"

using namespace cocos2d;

ExecuteButton* ExecuteButton::create()
{
	ExecuteButton* instance = new ExecuteButton();

	instance->autorelease();

	return instance;
}

ExecuteButton::ExecuteButton()
{
	LocalizedLabel*	executeLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Execute::create());
	LocalizedLabel*	executeLabelHover = executeLabel->clone();

	executeLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	executeLabel->enableGlow(Color4B::BLACK);

	executeLabelHover->setColor(Color3B::YELLOW);
	executeLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	executeLabelHover->enableGlow(Color4B::ORANGE);

	this->executeButton = ClickableTextNode::create(
		executeLabel,
		executeLabelHover,
		CipherResources::Buttons_RunButton,
		CipherResources::Buttons_RunButtonSelected);

	this->addChild(this->executeButton);
}

ExecuteButton::~ExecuteButton()
{
}

void ExecuteButton::onEnter()
{
	super::onEnter();
}

void ExecuteButton::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->executeButton->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter, visibleSize.height / 2.0f - 420.0f));
}

void ExecuteButton::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void ExecuteButton::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}
