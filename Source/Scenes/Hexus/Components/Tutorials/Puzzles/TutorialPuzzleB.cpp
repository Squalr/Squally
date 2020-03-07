#include "TutorialPuzzleB.h"

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

TutorialPuzzleB* TutorialPuzzleB::create()
{
	TutorialPuzzleB* instance = new TutorialPuzzleB();

	instance->autorelease();

	return instance;
}

TutorialPuzzleB::TutorialPuzzleB() : super(GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->introTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleB_A_4Bits::create()->setStringReplacementVariables(Strings::Hexus_Hexus::create()), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->decimalCardsTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_PuzzleB_B_Overflow::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);

	LocalizedLabel* introNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* introNextLabelSelected = introNextLabel->clone();

	introNextLabel->enableOutline(Color4B::BLACK, 2);
	introNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->introNextButton = ClickableTextNode::create(introNextLabel, introNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));
	
	LocalizedLabel* decimalCardsNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* decimalCardsNextLabelSelected = decimalCardsNextLabel->clone();

	decimalCardsNextLabel->enableOutline(Color4B::BLACK, 2);
	decimalCardsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->decimalCardsNextButton = ClickableTextNode::create(decimalCardsNextLabel, decimalCardsNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->introTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->decimalCardsTutorialLabel->enableOutline(Color4B::BLACK, 2);

	this->introTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->decimalCardsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->addChild(this->focusTakeOver);
	this->addChild(this->introTutorialLabel);
	this->addChild(this->decimalCardsTutorialLabel);

	this->addChild(this->introNextButton);
	this->addChild(this->decimalCardsNextButton);
}

TutorialPuzzleB::~TutorialPuzzleB()
{
}

void TutorialPuzzleB::onEnter()
{
	super::onEnter();

	this->introTutorialLabel->setOpacity(0);
	this->decimalCardsTutorialLabel->setOpacity(0);

	this->introNextButton->disableInteraction(0);
	this->decimalCardsNextButton->disableInteraction(0);
}

void TutorialPuzzleB::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->introTutorialLabel->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f + 32.0f);
	this->decimalCardsTutorialLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f + 32.0f);
	
	this->introNextButton->setPosition(visibleSize.width / 2.0f, visibleSize.height / 2.0f - 32.0f);
	this->decimalCardsNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 32.0f);
}

void TutorialPuzzleB::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialPuzzleB::tryHijackState(GameState* gameState)
{
	this->initializeCallbacks(gameState);
	this->runTutorialIntro(gameState);

	return true;
}

void TutorialPuzzleB::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialPuzzleB::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialPuzzleB::initializeCallbacks(GameState* gameState)
{
	this->introNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->runTutorialDecimalCards(gameState);
	});
	this->decimalCardsNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](InputEvents::InputArgs* args)
	{
		this->introNextButton->interact();
		this->decimalCardsNextButton->interact();
	});
}

void TutorialPuzzleB::runTutorialIntro(GameState* gameState)
{
	this->introNextButton->enableInteraction(0);
	this->introNextButton->runAction(FadeTo::create(0.25f, 255));
	this->introTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	
	this->focusTakeOver->focus({ });
}

void TutorialPuzzleB::runTutorialDecimalCards(GameState* gameState)
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

void TutorialPuzzleB::unHijackState(GameState* gameState)
{
	this->decimalCardsNextButton->disableInteraction();
	this->decimalCardsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->decimalCardsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->focusTakeOver->unfocus();
}
