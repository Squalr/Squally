#include "TutorialAIntroSequence.h"

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

#include "Strings/Hexus/Tutorials/A/BinCards.h"
#include "Strings/Hexus/Tutorials/A/DecCards.h"
#include "Strings/Hexus/Tutorials/A/HandCards.h"
#include "Strings/Hexus/Tutorials/A/HexCards.h"
#include "Strings/Hexus/Tutorials/A/LossDisplay.h"
#include "Strings/Hexus/Tutorials/A/RowTotals.h"
#include "Strings/Hexus/Tutorials/A/ScoreTotals.h"
#include "Strings/Menus/GotIt.h"
#include "Strings/Menus/Next.h"

using namespace cocos2d;

TutorialAIntroSequence* TutorialAIntroSequence::create()
{
	TutorialAIntroSequence* instance = new TutorialAIntroSequence();

	instance->autorelease();

	return instance;
}

TutorialAIntroSequence::TutorialAIntroSequence() : super(StateOverride::TutorialMode::TutorialA, GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->scoreTotalsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_ScoreTotals::create(), Size(420.0f, 0.0f), TextHAlignment::CENTER);
	this->lossDisplayTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_LossDisplay::create(), Size(420.0f, 0.0f), TextHAlignment::CENTER);
	this->rowTotalsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_RowTotals::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->binaryCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_BinCards::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->decimalCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_DecCards::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->hexCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_HexCards::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->handCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_HandCards::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);

	this->helpArrowScoreTotals = HelpArrow::create();
	this->helpArrowLossDisplay = HelpArrow::create();
	this->helpArrowRowTotals = HelpArrow::create();
	this->helpArrowHandCards = HelpArrow::create();

	LocalizedLabel* scoreTotalsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* scoreTotalsNextLabelSelected = scoreTotalsNextLabel->clone();

	scoreTotalsNextLabel->enableOutline(Color4B::BLACK, 2);
	scoreTotalsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsNextButton = ClickableTextNode::create(scoreTotalsNextLabel, scoreTotalsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));
	
	LocalizedLabel* lossesDisplayNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* lossesDisplayNextLabelSelected = lossesDisplayNextLabel->clone();

	lossesDisplayNextLabel->enableOutline(Color4B::BLACK, 2);
	lossesDisplayNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lossDisplayNextButton = ClickableTextNode::create(lossesDisplayNextLabel, lossesDisplayNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* rowTotalsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* rowTotalsNextLabelSelected = rowTotalsNextLabel->clone();

	rowTotalsNextLabel->enableOutline(Color4B::BLACK, 2);
	rowTotalsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->rowTotalsNextButton = ClickableTextNode::create(rowTotalsNextLabel, rowTotalsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* binaryCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* binaryCardsNextLabelSelected = binaryCardsNextLabel->clone();

	binaryCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	binaryCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->binaryCardsNextButton = ClickableTextNode::create(binaryCardsNextLabel, binaryCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* decimalCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* decimalCardsNextLabelSelected = decimalCardsNextLabel->clone();

	decimalCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	decimalCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->decimalCardsNextButton = ClickableTextNode::create(decimalCardsNextLabel, decimalCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* hexCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* hexCardsNextLabelSelected = hexCardsNextLabel->clone();

	hexCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	hexCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->hexCardsNextButton = ClickableTextNode::create(hexCardsNextLabel, hexCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	LocalizedLabel* handCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());
	LocalizedLabel* handCardsNextLabelSelected = handCardsNextLabel->clone();

	handCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	handCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->handCardsNextButton = ClickableTextNode::create(handCardsNextLabel, handCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->scoreTotalsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->lossDisplayTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->rowTotalsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->binaryCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->hexCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->handCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->lossDisplayTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->rowTotalsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->binaryCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->decimalCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->hexCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->handCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->helpArrowScoreTotals->setRotation(-90.0f);
	this->helpArrowLossDisplay->setRotation(0.0f);
	this->helpArrowRowTotals->setRotation(-90.0f);
	this->helpArrowHandCards->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->scoreTotalsTutorialLabel);
	this->addChild(this->lossDisplayTutorialLabel);
	this->addChild(this->binaryCardsTutorialLabel);
	this->addChild(this->decimalCardsTutorialLabel);
	this->addChild(this->hexCardsTutorialLabel);
	this->addChild(this->rowTotalsTutorialLabel);
	this->addChild(this->handCardsTutorialLabel);

	this->addChild(this->scoreTotalsNextButton);
	this->addChild(this->lossDisplayNextButton);
	this->addChild(this->binaryCardsNextButton);
	this->addChild(this->decimalCardsNextButton);
	this->addChild(this->hexCardsNextButton);
	this->addChild(this->rowTotalsNextButton);
	this->addChild(this->handCardsNextButton);

	this->addChild(this->helpArrowScoreTotals);
	this->addChild(this->helpArrowLossDisplay);
	this->addChild(this->helpArrowRowTotals);
	this->addChild(this->helpArrowHandCards);
}

TutorialAIntroSequence::~TutorialAIntroSequence()
{
}

void TutorialAIntroSequence::onEnter()
{
	super::onEnter();

	this->scoreTotalsTutorialLabel->setOpacity(0);
	this->lossDisplayTutorialLabel->setOpacity(0);
	this->binaryCardsTutorialLabel->setOpacity(0);
	this->decimalCardsTutorialLabel->setOpacity(0);
	this->hexCardsTutorialLabel->setOpacity(0);
	this->rowTotalsTutorialLabel->setOpacity(0);
	this->handCardsTutorialLabel->setOpacity(0);

	this->scoreTotalsNextButton->disableInteraction(0);
	this->lossDisplayNextButton->disableInteraction(0);
	this->rowTotalsNextButton->disableInteraction(0);
	this->binaryCardsNextButton->disableInteraction(0);
	this->decimalCardsNextButton->disableInteraction(0);
	this->hexCardsNextButton->disableInteraction(0);
	this->handCardsNextButton->disableInteraction(0);
}

void TutorialAIntroSequence::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scoreTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 32.0f);
	this->lossDisplayTutorialLabel->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f + 32.0f);
	this->rowTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	this->binaryCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	this->decimalCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	this->hexCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	this->handCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	
	this->scoreTotalsNextButton->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 32.0f);
	this->lossDisplayNextButton->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 32.0f);
	this->rowTotalsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
	this->binaryCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
	this->decimalCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
	this->hexCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
	this->handCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	
	this->helpArrowScoreTotals->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX - 144.0f, visibleSize.height / 2.0f + Config::totalAttackOffsetY));
	this->helpArrowLossDisplay->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + (Config::socketAOffsetX + Config::socketBOffsetX) / 2.0f, visibleSize.height / 2.0f + Config::socketOffsetY + 128.0f));
	this->helpArrowRowTotals->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter + Config::cardTotalOffsetX - 144.0f, visibleSize.height / 2.0f - 288.0f));
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 288.0f));
}

void TutorialAIntroSequence::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialAIntroSequence::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialScoreTotal(gameState);

	return true;
}

void TutorialAIntroSequence::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialAIntroSequence::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialAIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->scoreTotalsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialLossDisplay(gameState);
	});
	this->lossDisplayNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialRowTotals(gameState);
	});
	this->rowTotalsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialBinaryCards(gameState);
	});
	this->binaryCardsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialDecimalCards(gameState);
	});
	this->decimalCardsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialHexCards(gameState);
	});
	this->hexCardsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialHandCards(gameState);
	});
	this->handCardsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialAIntroSequence::runTutorialScoreTotal(GameState* gameState)
{
	this->scoreTotalsNextButton->enableInteraction(0);
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowScoreTotals->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->scoreTotalPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::runTutorialLossDisplay(GameState* gameState)
{
	this->scoreTotalsNextButton->disableInteraction();
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowScoreTotals->hidePointer();
	this->lossDisplayNextButton->enableInteraction(0);
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 255));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowLossDisplay->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->lossesDisplayPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::runTutorialRowTotals(GameState* gameState)
{
	this->lossDisplayNextButton->disableInteraction();
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 0));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowLossDisplay->hidePointer();
	this->rowTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowRowTotals->showPointer();

	this->runAction(Sequence::create(
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->enemyHexCards);
			focusTargets.push_back(gameState->enemyHexRowTotalPointer);
			this->focusTakeOver->focus(focusTargets);
			this->helpArrowRowTotals->setPositionY(gameState->enemyHexRowTotalPointer->getPositionY());
		}),
		DelayTime::create(2.5f),
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->enemyDecimalCards);
			focusTargets.push_back(gameState->enemyDecimalRowTotalPointer);
			this->focusTakeOver->focus(focusTargets);
			this->helpArrowRowTotals->setPositionY(gameState->enemyDecimalRowTotalPointer->getPositionY());
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->enemyBinaryCards);
			focusTargets.push_back(gameState->enemyBinaryRowTotalPointer);
			this->focusTakeOver->focus(focusTargets);
			this->helpArrowRowTotals->setPositionY(gameState->enemyBinaryRowTotalPointer->getPositionY());
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			focusTargets.push_back(gameState->playerDecimalCards);
			focusTargets.push_back(gameState->playerDecimalRowTotalPointer);
			this->focusTakeOver->focus(focusTargets);
			this->helpArrowRowTotals->setPositionY(gameState->playerDecimalRowTotalPointer->getPositionY());
		}),
		DelayTime::create(1.5f),
		CallFunc::create([=]()
		{
			std::vector<Node*> focusTargets = std::vector<Node*>();
			this->focusTakeOver->focus(focusTargets);
			this->rowTotalsNextButton->enableInteraction(0);
			this->rowTotalsNextButton->runAction(FadeTo::create(0.25f, 255));
			this->helpArrowRowTotals->hidePointer();
		}),
		nullptr
	));
}

void TutorialAIntroSequence::runTutorialBinaryCards(GameState* gameState)
{
	this->rowTotalsNextButton->disableInteraction();
	this->rowTotalsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->rowTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->binaryCardsNextButton->enableInteraction(0);
	this->binaryCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->binaryCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->enemyBinaryCards);
	focusTargets.push_back(gameState->playerBinaryCards);
	for (auto it = gameState->playerHand->rowCards.begin(); it != gameState->playerHand->rowCards.end(); it++)
	{
		if ((*it)->cardData->cardType == CardData::CardType::Binary)
		{
			focusTargets.push_back((*it));
		}
	}
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::runTutorialDecimalCards(GameState* gameState)
{
	this->binaryCardsNextButton->disableInteraction();
	this->binaryCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->binaryCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->decimalCardsNextButton->enableInteraction(0);
	this->decimalCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->decimalCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->enemyDecimalCards);
	focusTargets.push_back(gameState->playerDecimalCards);
	for (auto it = gameState->playerHand->rowCards.begin(); it != gameState->playerHand->rowCards.end(); it++)
	{
		if ((*it)->cardData->cardType == CardData::CardType::Decimal)
		{
			focusTargets.push_back((*it));
		}
	}
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::runTutorialHexCards(GameState* gameState)
{
	this->decimalCardsNextButton->disableInteraction();
	this->decimalCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->decimalCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowRowTotals->hidePointer();
	this->hexCardsNextButton->enableInteraction(0);
	this->hexCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->hexCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->enemyHexCards);
	focusTargets.push_back(gameState->playerHexCards);
	for (auto it = gameState->playerHand->rowCards.begin(); it != gameState->playerHand->rowCards.end(); it++)
	{
		if ((*it)->cardData->cardType == CardData::CardType::Hexidecimal)
		{
			focusTargets.push_back((*it));
		}
	}
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::runTutorialHandCards(GameState* gameState)
{
	this->hexCardsNextButton->disableInteraction();
	this->hexCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->hexCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->handCardsNextButton->enableInteraction(0);
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->playerHand);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAIntroSequence::concludeTutorial(GameState* gameState)
{
	this->handCardsNextButton->disableInteraction();
	this->handCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->handCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();
	this->focusTakeOver->unfocus();

	this->unHijackState(gameState);
}
