#include "CipherShiftLeftTutorial.h"

#include <vector>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/2d/CCSprite.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Cipher/CipherState.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CipherShiftLeftTutorial::MapKeyTutorial = "shift-left";

CipherShiftLeftTutorial* CipherShiftLeftTutorial::create()
{
	CipherShiftLeftTutorial* instance = new CipherShiftLeftTutorial();

	instance->autorelease();

	return instance;
}

CipherShiftLeftTutorial::CipherShiftLeftTutorial() : super(CipherState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_Connect_ChestsLocked::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);
	this->connectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_Connect_ThisOneIsEasy::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);

	LocalizedLabel* introNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* introNextLabelSelected = introNextLabel->clone();

	introNextLabel->enableOutline(Color4B::BLACK, 2);
	introNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonIntro = ClickableTextNode::create(introNextLabel, introNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* connectNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* connectNextLabelSelected = introNextLabel->clone();

	connectNextLabel->enableOutline(Color4B::BLACK, 2);
	connectNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonConnect = ClickableTextNode::create(connectNextLabel, connectNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introLabel);
	this->addChild(this->connectLabel);
	this->addChild(this->nextButtonIntro);
	this->addChild(this->nextButtonConnect);
}

CipherShiftLeftTutorial::~CipherShiftLeftTutorial()
{
}

void CipherShiftLeftTutorial::onEnter()
{
	super::onEnter();

	this->introLabel->setOpacity(0);
	this->connectLabel->setOpacity(0);

	this->nextButtonIntro->disableInteraction(0);
	this->nextButtonConnect->disableInteraction(0);
}

void CipherShiftLeftTutorial::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	this->connectLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	
	this->nextButtonIntro->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
	this->nextButtonConnect->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
}

void CipherShiftLeftTutorial::initializeListeners()
{
	super::initializeListeners();
}

bool CipherShiftLeftTutorial::tryHijackState(CipherState* cipherState)
{
	this->initializeCallbacks(cipherState);

	this->runTutorialPartA(cipherState);

	return true;
}

void CipherShiftLeftTutorial::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherShiftLeftTutorial::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}

void CipherShiftLeftTutorial::initializeCallbacks(CipherState* cipherState)
{
	this->nextButtonIntro->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialPartB(cipherState);
	});
	this->nextButtonConnect->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(cipherState);
	});
}

void CipherShiftLeftTutorial::runTutorialPartA(CipherState* cipherState)
{
	this->nextButtonIntro->enableInteraction(0);
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 255));
	this->introLabel->runAction(FadeTo::create(0.25f, 255));

	this->focusTakeOver->focus({ });
}

void CipherShiftLeftTutorial::runTutorialPartB(CipherState* cipherState)
{
	this->nextButtonIntro->disableInteraction();
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 0));
	this->introLabel->runAction(FadeTo::create(0.25f, 0));
	this->nextButtonConnect->enableInteraction(0);
	this->nextButtonConnect->runAction(FadeTo::create(0.25f, 255));
	this->connectLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(cipherState->inputContent);
	focusTargets.push_back(cipherState->outputContent);
	this->focusTakeOver->focus(focusTargets);
}

void CipherShiftLeftTutorial::unHijackState(CipherState* cipherState)
{
	this->nextButtonIntro->disableInteraction();
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 0));
	this->introLabel->runAction(FadeTo::create(0.25f, 0));
	this->nextButtonConnect->disableInteraction();
	this->nextButtonConnect->runAction(FadeTo::create(0.25f, 0));
	this->connectLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
