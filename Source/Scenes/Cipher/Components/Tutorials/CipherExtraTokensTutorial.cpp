#include "CipherExtraTokensTutorial.h"

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

const std::string CipherExtraTokensTutorial::MapKeyTutorial = "extra-tokens";

CipherExtraTokensTutorial* CipherExtraTokensTutorial::create()
{
	CipherExtraTokensTutorial* instance = new CipherExtraTokensTutorial();

	instance->autorelease();

	return instance;
}

CipherExtraTokensTutorial::CipherExtraTokensTutorial() : super(CipherState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Cipher_Tutorials_ExtraTokens_A_ExtraTokens::create(), Size(512.0f, 0.0f), TextHAlignment::CENTER);
	
	this->introLabel->enableOutline(Color4B::BLACK, 2);

	LocalizedLabel* introNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* introNextLabelSelected = introNextLabel->clone();

	introNextLabel->enableOutline(Color4B::BLACK, 2);
	introNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->nextButtonIntro = ClickableTextNode::create(introNextLabel, introNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introLabel);
	this->addChild(this->nextButtonIntro);
}

CipherExtraTokensTutorial::~CipherExtraTokensTutorial()
{
}

void CipherExtraTokensTutorial::onEnter()
{
	super::onEnter();

	this->introLabel->setOpacity(0);

	this->nextButtonIntro->disableInteraction(0);
}

void CipherExtraTokensTutorial::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 64.0f);
	
	this->nextButtonIntro->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 64.0f);
}

void CipherExtraTokensTutorial::initializeListeners()
{
	super::initializeListeners();
}

bool CipherExtraTokensTutorial::tryHijackState(CipherState* cipherState)
{
	this->initializeCallbacks(cipherState);

	this->runTutorialPartA(cipherState);

	return true;
}

void CipherExtraTokensTutorial::onBeforeStateChange(CipherState* cipherState)
{
	super::onBeforeStateChange(cipherState);
}

void CipherExtraTokensTutorial::onAnyStateChange(CipherState* cipherState)
{
	super::onAnyStateChange(cipherState);
}

void CipherExtraTokensTutorial::initializeCallbacks(CipherState* cipherState)
{
	this->nextButtonIntro->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(cipherState);
	});

	this->whenKeyPressed({ InputEvents::KeyCode::KEY_SPACE }, [=](InputEvents::KeyboardEventArgs* args)
	{
		this->nextButtonIntro->interact();
	});
}

void CipherExtraTokensTutorial::runTutorialPartA(CipherState* cipherState)
{
	this->nextButtonIntro->enableInteraction(0);
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 255));
	this->introLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(cipherState->blockContent);
	this->focusTakeOver->focus(focusTargets);
}

void CipherExtraTokensTutorial::unHijackState(CipherState* cipherState)
{
	this->nextButtonIntro->disableInteraction();
	this->nextButtonIntro->runAction(FadeTo::create(0.25f, 0));
	this->introLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
