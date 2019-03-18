#include "TutorialCIntroSequence.h"

#include <vector>

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/FocusTakeOver.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Hexus/Tutorials/C/NotEnoughToWin.h"
#include "Strings/Hexus/Tutorials/C/OpponentLead.h"
#include "Strings/Hexus/Tutorials/C/UseSurrender.h"
#include "Strings/Menus/GotIt.h"
#include "Strings/Menus/Next.h"

using namespace cocos2d;

TutorialCIntroSequence* TutorialCIntroSequence::create()
{
	TutorialCIntroSequence* instance = new TutorialCIntroSequence();

	instance->autorelease();

	return instance;
}

TutorialCIntroSequence::TutorialCIntroSequence() : super(StateOverride::TutorialMode::TutorialC, GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->scoreTotalsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_C_OpponentLead::create(), Size(420.0f, 0.0f));
	this->handCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_C_NotEnoughToWin::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->lastStandTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_C_UseSurrender::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->helpArrowScoreTotals = HelpArrow::create();
	this->helpArrowHandCards = HelpArrow::create();
	this->helpArrowLastStand = HelpArrow::create();

	LocalizedLabel* scoreTotalsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* scoreTotalsNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());

	scoreTotalsNextLabel->enableOutline(Color4B::BLACK, 2);
	scoreTotalsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsNextButton = ClickableTextNode::create(scoreTotalsNextLabel, scoreTotalsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* handCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* handCardsNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());

	handCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	handCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->handCardsNextButton = ClickableTextNode::create(handCardsNextLabel, handCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* lastStandNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());
	LocalizedLabel* lastStandNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());

	lastStandNextLabel->enableOutline(Color4B::BLACK, 2);
	lastStandNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lastStandNextButton = ClickableTextNode::create(lastStandNextLabel, lastStandNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->scoreTotalsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->handCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->lastStandTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->handCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->lastStandTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->helpArrowScoreTotals->setRotation(-90.0f);
	this->helpArrowHandCards->setRotation(0.0f);
	this->helpArrowLastStand->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->scoreTotalsTutorialLabel);
	this->addChild(this->handCardsTutorialLabel);
	this->addChild(this->lastStandTutorialLabel);

	this->addChild(this->scoreTotalsNextButton);
	this->addChild(this->handCardsNextButton);
	this->addChild(this->lastStandNextButton);

	this->addChild(this->helpArrowScoreTotals);
	this->addChild(this->helpArrowHandCards);
	this->addChild(this->helpArrowLastStand);
}

TutorialCIntroSequence::~TutorialCIntroSequence()
{
}

void TutorialCIntroSequence::onEnter()
{
	super::onEnter();

	this->scoreTotalsTutorialLabel->setOpacity(0);
	this->handCardsTutorialLabel->setOpacity(0);
	this->lastStandTutorialLabel->setOpacity(0);

	this->scoreTotalsNextButton->disableInteraction(0);
	this->handCardsNextButton->disableInteraction(0);
	this->lastStandNextButton->disableInteraction(0);
}

void TutorialCIntroSequence::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scoreTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 32.0f);
	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	this->lastStandTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + 32.0f);
	
	this->scoreTotalsNextButton->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 32.0f);
	this->handCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	this->lastStandNextButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - 32.0f);
	
	this->helpArrowScoreTotals->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX - 144.0f, visibleSize.height / 2.0f + Config::totalAttackOffsetY));
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 288.0f));
	this->helpArrowLastStand->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY + 144.0f);
}

void TutorialCIntroSequence::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialCIntroSequence::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialScoreTotal(gameState);

	return true;
}

void TutorialCIntroSequence::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialCIntroSequence::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialCIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->scoreTotalsNextButton->setClickCallback([=](MouseEvents::MouseEventArgs* args)
	{
		this->runTutorialHandCards(gameState);
	});
	this->handCardsNextButton->setClickCallback([=](MouseEvents::MouseEventArgs* args)
	{
		this->runTutorialLastStand(gameState);
	});
	this->lastStandNextButton->setClickCallback([=](MouseEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialCIntroSequence::runTutorialScoreTotal(GameState* gameState)
{
	this->scoreTotalsNextButton->enableInteraction(0);
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowScoreTotals->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->scoreTotalPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialCIntroSequence::runTutorialHandCards(GameState* gameState)
{
	this->scoreTotalsNextButton->disableInteraction();
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowScoreTotals->hidePointer();

	this->handCardsNextButton->enableInteraction(0);
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->playerHand);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialCIntroSequence::runTutorialLastStand(GameState* gameState)
{
	this->handCardsNextButton->disableInteraction();
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();

	this->lastStandNextButton->enableInteraction(0);
	this->lastStandNextButton->runAction(FadeTo::create(0.25f, 255));
	this->lastStandTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowLastStand->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->passButtonPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialCIntroSequence::concludeTutorial(GameState* gameState)
{
	this->lastStandNextButton->disableInteraction();
	this->lastStandNextButton->runAction(FadeTo::create(0.25f, 0));
	this->lastStandTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowLastStand->hidePointer();

	this->focusTakeOver->unfocus();
	this->unHijackState(gameState);
}
