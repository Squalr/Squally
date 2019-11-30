#include "TestButton.h"

#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Scenes/Cipher/Config.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/CipherResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TestButton* TestButton::create()
{
	TestButton* instance = new TestButton();

	instance->autorelease();

	return instance;
}

TestButton::TestButton()
{
	this->activeCipherState = nullptr;

	LocalizedLabel*	testLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Cipher_Test::create());
	LocalizedLabel*	testLabelHover = testLabel->clone();

	testLabel->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	testLabel->enableGlow(Color4B::BLACK);

	testLabelHover->setColor(Color3B::YELLOW);
	testLabelHover->enableShadow(Color4B::BLACK, Size(-2.0f, -2.0f), 2);
	testLabelHover->enableGlow(Color4B::ORANGE);

	this->testButton = ClickableTextNode::create(
		testLabel,
		testLabelHover,
		CipherResources::Buttons_TestRunButton,
		CipherResources::Buttons_TestRunButtonSelected);

	this->addChild(this->testButton);
}

TestButton::~TestButton()
{
}

void TestButton::onEnter()
{
	super::onEnter();
}

void TestButton::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->testButton->setPosition(Vec2(visibleSize.width / 2.0f + Config::LeftColumnCenter + 256.0f, visibleSize.height / 2.0f - 420.0f));
}

void TestButton::initializeListeners()
{
	super::initializeListeners();

	this->testButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		if (this->activeCipherState != nullptr)
		{
			this->activeCipherState->updateState(this->activeCipherState, CipherState::StateType::Testing);
		}
	});
}

void TestButton::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);

	switch(cipherState->stateType)
	{
		case CipherState::StateType::Neutral:
		{
			this->testButton->enableInteraction();
			break;
		}
		default:
		{
			this->testButton->disableInteraction();
			break;
		}
	}

	this->activeCipherState = cipherState;
}
