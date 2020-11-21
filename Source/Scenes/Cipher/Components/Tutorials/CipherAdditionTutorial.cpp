#include "CipherAdditionTutorial.h"

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
#include "Scenes/Cipher/Components/DisplayModeToggles.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

const std::string CipherAdditionTutorial::MapKeyTutorial = "addition";

CipherAdditionTutorial* CipherAdditionTutorial::create()
{
	CipherAdditionTutorial* instance = new CipherAdditionTutorial();

	instance->autorelease();

	return instance;
}

CipherAdditionTutorial::CipherAdditionTutorial() : super(CipherState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_Addition_A_DisplayedAs::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);
	this->buttonsLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_Addition_B_ChangeDataType::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);
	this->connectLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_Addition_C_ConnectComponents::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);

	this->introLabel->enableOutline(Color4B::BLACK, 2);
	this->buttonsLabel->enableOutline(Color4B::BLACK, 2);
	this->connectLabel->enableOutline(Color4B::BLACK, 2);

	LocalizedLabel* introNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* introNextLabelSelected = introNextLabel->clone();

	introNextLabel->enableOutline(Color4B::BLACK, 2);
	introNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonIntro = ClickableTextNode::create(introNextLabel, introNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));
	
	LocalizedLabel* buttonNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* buttonNextLabelSelected = buttonNextLabel->clone();

	buttonNextLabel->enableOutline(Color4B::BLACK, 2);
	buttonNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonButtons = ClickableTextNode::create(buttonNextLabel, buttonNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* connectNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* connectNextLabelSelected = introNextLabel->clone();

	connectNextLabel->enableOutline(Color4B::BLACK, 2);
	connectNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonConnect = ClickableTextNode::create(connectNextLabel, connectNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introLabel);
	this->addChild(this->buttonsLabel);
	this->addChild(this->connectLabel);
	this->addChild(this->nextButtonIntro);
	this->addChild(this->nextButtonButtons);
	this->addChild(this->nextButtonConnect);
}

CipherAdditionTutorial::~CipherAdditionTutorial()
{
}

void CipherAdditionTutorial::onEnter()
{
	super::onEnter();

	this->introLabel->setOpacity(0);
	this->buttonsLabel->setOpacity(0);
	this->connectLabel->setOpacity(0);

	this->nextButtonIntro->disableInteraction(0);
	this->nextButtonButtons->disableInteraction(0);
	this->nextButtonConnect->disableInteraction(0);
}

void CipherAdditionTutorial::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	this->buttonsLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	this->connectLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	
	this->nextButtonIntro->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
	this->nextButtonButtons->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
	this->nextButtonConnect->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
}

void CipherAdditionTutorial::initializeListeners()
{
	super::initializeListeners();
}

bool CipherAdditionTutorial::tryHijackState(CipherState* cipherState)
{
	this->initializeCallbacks(cipherState);

	this->runTutorialPartA(cipherState);

	return true;
}

void CipherAdditionTutorial::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherAdditionTutorial::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}

void CipherAdditionTutorial::initializeCallbacks(CipherState* cipherState)
{
	this->nextButtonIntro->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialPartB(cipherState);
	});
	this->nextButtonButtons->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialPartC(cipherState);
	});
	this->nextButtonConnect->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(cipherState);
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->nextButtonIntro->interact();
		this->nextButtonButtons->interact();
		this->nextButtonConnect->interact();
	});
}

void CipherAdditionTutorial::runTutorialPartA(CipherState* cipherState)
{
	this->nextButtonIntro->enableInteraction(0);
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 255));
	this->introLabel->runAction(FadeTo::create(0.25f, 255));

	this->focusTakeOver->focus({ });
}

void CipherAdditionTutorial::runTutorialPartB(CipherState* cipherState)
{
	this->nextButtonIntro->disableInteraction();
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 0));
	this->introLabel->runAction(FadeTo::create(0.25f, 0));
	this->nextButtonButtons->enableInteraction(0);
	this->nextButtonButtons->runAction(FadeTo::create(0.25f, 255));
	this->buttonsLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(cipherState->displayModeTogglesPointer);
	this->focusTakeOver->focus(focusTargets);
}

void CipherAdditionTutorial::runTutorialPartC(CipherState* cipherState)
{
	this->nextButtonButtons->disableInteraction();
	this->nextButtonButtons->runAction(FadeTo::create(0.25f, 0));
	this->buttonsLabel->runAction(FadeTo::create(0.25f, 0));
	this->nextButtonConnect->enableInteraction(0);
	this->nextButtonConnect->runAction(FadeTo::create(0.25f, 255));
	this->connectLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(cipherState->inputContent);
	focusTargets.push_back(cipherState->blockContent);
	focusTargets.push_back(cipherState->outputContent);
	this->focusTakeOver->focus(focusTargets);
}

void CipherAdditionTutorial::unHijackState(CipherState* cipherState)
{
	this->nextButtonIntro->disableInteraction();
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 0));
	this->introLabel->runAction(FadeTo::create(0.25f, 0));
	this->nextButtonConnect->disableInteraction();
	this->nextButtonConnect->runAction(FadeTo::create(0.25f, 0));
	this->connectLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
