#include "TutorialPuzzleShlOverflow.h"

#include <vector>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialPuzzleShlOverflow* TutorialPuzzleShlOverflow::create()
{
	TutorialPuzzleShlOverflow* instance = new TutorialPuzzleShlOverflow();

	instance->autorelease();

	return instance;
}

TutorialPuzzleShlOverflow::TutorialPuzzleShlOverflow() : super(GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleC_A_Overflow::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->introNextButton = this->createNextButton();

	this->introTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->introTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introTutorialLabel);

	this->addChild(this->introNextButton);
}

TutorialPuzzleShlOverflow::~TutorialPuzzleShlOverflow()
{
}

void TutorialPuzzleShlOverflow::onEnter()
{
	super::onEnter();

	this->introTutorialLabel->setOpacity(0);

	this->introNextButton->disableInteraction(0);
}

void TutorialPuzzleShlOverflow::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introTutorialLabel->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f);
	
	this->introNextButton->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 32.0f);
}

void TutorialPuzzleShlOverflow::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialPuzzleShlOverflow::tryHijackState(GameState* gameState)
{
	this->defer([=]()
	{
		this->initializeCallbacks(gameState);
		this->runTutorialIntro(gameState);
	});

	return true;
}

void TutorialPuzzleShlOverflow::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialPuzzleShlOverflow::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialPuzzleShlOverflow::initializeCallbacks(GameState* gameState)
{
	this->introNextButton->setMouseClickCallback([=](MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](KeyboardEventArgs* args)
	{
		this->introNextButton->interact();
	});
}

void TutorialPuzzleShlOverflow::runTutorialIntro(GameState* gameState)
{
	this->introNextButton->enableInteraction(0);
	this->introNextButton->runAction(FadeTo::create(0.25f, 255));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	
	this->focusTakeOver->focus({ });
}

void TutorialPuzzleShlOverflow::unHijackState(GameState* gameState)
{
	this->introNextButton->disableInteraction();
	this->introNextButton->runAction(FadeTo::create(0.25f, 0));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
