#include "TutorialPuzzleOverflow.h"

#include <vector>

#include "cocos/2d/CCActionInstant.h"
#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/CardPreview.h"
#include "Scenes/Hexus/Components/CardPreviewComponent.h"
#include "Scenes/Hexus/GameState.h"
#include "Scenes/Hexus/HexusConfig.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

TutorialPuzzleOverflow* TutorialPuzzleOverflow::create()
{
	TutorialPuzzleOverflow* instance = new TutorialPuzzleOverflow();

	instance->autorelease();

	return instance;
}

TutorialPuzzleOverflow::TutorialPuzzleOverflow() : super(GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleB_A_4Bits::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->decimalCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleB_B_Overflow::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->helpTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleB_C_HelpMenu::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->introNextButton = this->createNextButton();
	this->decimalCardsNextButton = this->createNextButton();
	this->helpNextButton = this->createNextButton();
	this->helpArrow = HelpArrow::create();

	this->helpArrow->setRotation(270.0f);

	this->introTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->helpTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->introTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->decimalCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introTutorialLabel);
	this->addChild(this->decimalCardsTutorialLabel);
	this->addChild(this->helpTutorialLabel);
	this->addChild(this->introNextButton);
	this->addChild(this->decimalCardsNextButton);
	this->addChild(this->helpNextButton);
	this->addChild(this->helpArrow);
}

TutorialPuzzleOverflow::~TutorialPuzzleOverflow()
{
}

void TutorialPuzzleOverflow::onEnter()
{
	super::onEnter();

	this->introTutorialLabel->setOpacity(0);
	this->decimalCardsTutorialLabel->setOpacity(0);
	this->helpTutorialLabel->setOpacity(0);

	this->introNextButton->disableInteraction(0);
	this->decimalCardsNextButton->disableInteraction(0);
	this->helpNextButton->disableInteraction(0);
}

void TutorialPuzzleOverflow::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introTutorialLabel->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f);
	this->decimalCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	this->helpTutorialLabel->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	
	this->introNextButton->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 32.0f);
	this->decimalCardsNextButton->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
	this->helpNextButton->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);

	this->helpArrow->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter - 224.0f, visibleSize.height / 2.0f - 188.0f);
}

void TutorialPuzzleOverflow::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialPuzzleOverflow::tryHijackState(GameState* gameState)
{
	this->defer([=]()
	{
		this->initializeCallbacks(gameState);
		this->runTutorialIntro(gameState);
	});

	return true;
}

void TutorialPuzzleOverflow::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialPuzzleOverflow::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialPuzzleOverflow::initializeCallbacks(GameState* gameState)
{
	this->introNextButton->setMouseClickCallback([=](MouseEventArgs* args)
	{
		this->runTutorialDecimalCards(gameState);
	});
	this->decimalCardsNextButton->setMouseClickCallback([=](MouseEventArgs* args)
	{
		this->runTutorialHelp(gameState);
	});
	this->helpNextButton->setMouseClickCallback([=](MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](KeyboardEventArgs* args)
	{
		this->introNextButton->interact();
		this->decimalCardsNextButton->interact();
		this->helpNextButton->interact();
	});
}

void TutorialPuzzleOverflow::runTutorialIntro(GameState* gameState)
{
	this->introNextButton->enableInteraction(0);
	this->introNextButton->runAction(FadeTo::create(0.25f, 255));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	
	this->focusTakeOver->focus({ });
}

void TutorialPuzzleOverflow::runTutorialDecimalCards(GameState* gameState)
{
	this->introNextButton->disableInteraction();
	this->introNextButton->runAction(FadeTo::create(0.25f, 0));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->decimalCardsNextButton->enableInteraction(0);
	this->decimalCardsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->decimalCardsTutorialLabel->runAction(FadeTo::create(0.25f, 255));

	std::vector<Node*> focusTargets = std::vector<Node*>();

	focusTargets.push_back(gameState->enemyDecimalCards);
	focusTargets.push_back(gameState->playerDecimalCards);
	focusTargets.push_back(gameState->playerHand);

	this->focusTakeOver->focus(focusTargets);
}

void TutorialPuzzleOverflow::runTutorialHelp(GameState* gameState)
{
	this->decimalCardsNextButton->disableInteraction();
	this->decimalCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->decimalCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpNextButton->enableInteraction(0);
	this->helpNextButton->runAction(FadeTo::create(0.25f, 255));
	this->helpTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrow->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();

	if (!gameState->playerHand->rowCards.empty())
	{
		gameState->cardPreviewPointer->getCardPreview()->previewCard(gameState->playerHand->rowCards[0]);
	}

	focusTargets.push_back(gameState->cardPreviewPointer);

	this->focusTakeOver->focus(focusTargets);
}

void TutorialPuzzleOverflow::unHijackState(GameState* gameState)
{
	this->helpNextButton->disableInteraction();
	this->helpNextButton->runAction(FadeTo::create(0.25f, 0));
	this->helpTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrow->hidePointer();
	this->focusTakeOver->unfocus();
}
