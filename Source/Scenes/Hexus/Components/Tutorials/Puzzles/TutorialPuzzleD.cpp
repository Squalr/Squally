#include "TutorialPuzzleD.h"

#include <vector>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialPuzzleD* TutorialPuzzleD::create()
{
	TutorialPuzzleD* instance = new TutorialPuzzleD();

	instance->autorelease();

	return instance;
}

TutorialPuzzleD::TutorialPuzzleD() : super(GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleD_A_Order::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	
	LocalizedLabel* introNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* introNextLabelSelected = introNextLabel->clone();

	introNextLabel->enableOutline(Color4B::BLACK, 2);
	introNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->introNextButton = ClickableTextNode::create(introNextLabel, introNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));
	
	this->introTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->introTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introTutorialLabel);

	this->addChild(this->introNextButton);
}

TutorialPuzzleD::~TutorialPuzzleD()
{
}

void TutorialPuzzleD::onEnter()
{
	super::onEnter();

	this->introTutorialLabel->setOpacity(0);

	this->introNextButton->disableInteraction(0);
}

void TutorialPuzzleD::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introTutorialLabel->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f);
	
	this->introNextButton->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 32.0f);
}

void TutorialPuzzleD::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialPuzzleD::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialIntro(gameState);

	return true;
}

void TutorialPuzzleD::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialPuzzleD::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialPuzzleD::initializeCallbacks(GameState* gameState)
{
	this->introNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});
}

void TutorialPuzzleD::runTutorialIntro(GameState* gameState)
{
	this->introNextButton->enableInteraction(0);
	this->introNextButton->runAction(FadeTo::create(0.25f, 255));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	
	this->focusTakeOver->focus({ });
}

void TutorialPuzzleD::unHijackState(GameState* gameState)
{
	this->introNextButton->disableInteraction();
	this->introNextButton->runAction(FadeTo::create(0.25f, 0));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
