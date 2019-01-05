#include "TutorialDIntroSequence.h"

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

#include "Strings/Hexus/Tutorials/D/UseShiftRight.h"
#include "Strings/Menus/GotIt.h"

using namespace cocos2d;

TutorialDIntroSequence* TutorialDIntroSequence::create()
{
	TutorialDIntroSequence* instance = new TutorialDIntroSequence();

	instance->autorelease();

	return instance;
}

TutorialDIntroSequence::TutorialDIntroSequence() : TutorialBase(StateOverride::TutorialMode::TutorialD, GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->handCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_D_UseShiftRight::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->helpArrowHandCards = HelpArrow::create();

	LocalizedLabel* handCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());
	LocalizedLabel* handCardsNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());

	handCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	handCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->handCardsNextButton = ClickableTextNode::create(handCardsNextLabel, handCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->handCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->handCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpArrowHandCards->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->handCardsTutorialLabel);
	this->addChild(this->handCardsNextButton);
	this->addChild(this->helpArrowHandCards);
}

TutorialDIntroSequence::~TutorialDIntroSequence()
{
}

void TutorialDIntroSequence::onEnter()
{
	TutorialBase::onEnter();

	this->handCardsTutorialLabel->setOpacity(0);

	this->handCardsNextButton->disableInteraction(0);
}

void TutorialDIntroSequence::initializePositions()
{
	TutorialBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	this->handCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 288.0f));
}

void TutorialDIntroSequence::initializeListeners()
{
	TutorialBase::initializeListeners();
}

bool TutorialDIntroSequence::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialHandCards(gameState);

	return true;
}

void TutorialDIntroSequence::onBeforeStateChange(GameState* gameState)
{
	TutorialBase::onBeforeStateChange(gameState);
}

void TutorialDIntroSequence::onAnyStateChange(GameState* gameState)
{
	TutorialBase::onAnyStateChange(gameState);
}

void TutorialDIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->handCardsNextButton->setClickCallback([=](ClickableNode* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialDIntroSequence::runTutorialHandCards(GameState* gameState)
{
	this->handCardsNextButton->enableInteraction(0);
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->playerHand);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialDIntroSequence::concludeTutorial(GameState* gameState)
{
	this->handCardsNextButton->disableInteraction();
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();

	this->focusTakeOver->unfocus();
	this->unHijackState(gameState);
}
