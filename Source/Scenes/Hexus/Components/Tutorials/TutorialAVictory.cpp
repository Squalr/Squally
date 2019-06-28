#include "TutorialAVictory.h"

#include <vector>

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Hexus/Tutorials/A/Victory.h"
#include "Strings/Menus/Next.h"

using namespace cocos2d;

TutorialAVictory* TutorialAVictory::create()
{
	TutorialAVictory* instance = new TutorialAVictory();

	instance->autorelease();

	return instance;
}

TutorialAVictory::TutorialAVictory() : super(StateOverride::TutorialMode::TutorialA, GameState::StateType::GameEnd)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->lossDisplayTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_A_Victory::create(), Size(420.0f, 0.0f));
	this->helpArrowLossDisplay = HelpArrow::create();

	LocalizedLabel* lossesDisplayNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());
	LocalizedLabel* lossesDisplayNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_Next::create());

	lossesDisplayNextLabel->enableOutline(Color4B::BLACK, 2);
	lossesDisplayNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lossDisplayNextButton = ClickableTextNode::create(lossesDisplayNextLabel, lossesDisplayNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->lossDisplayTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->lossDisplayTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));

	this->helpArrowLossDisplay->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->lossDisplayTutorialLabel);
	this->addChild(this->lossDisplayNextButton);
	this->addChild(this->helpArrowLossDisplay);
}

TutorialAVictory::~TutorialAVictory()
{
}

void TutorialAVictory::onEnter()
{
	super::onEnter();

	this->lossDisplayTutorialLabel->setOpacity(0);
	this->lossDisplayNextButton->disableInteraction(0);
}

void TutorialAVictory::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->lossDisplayTutorialLabel->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f + 32.0f);
	this->lossDisplayNextButton->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 32.0f);
	this->helpArrowLossDisplay->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + (Config::socketAOffsetX + Config::socketBOffsetX) / 2.0f, visibleSize.height / 2.0f + Config::socketOffsetY + 128.0f));
}

void TutorialAVictory::initializeListeners()
{
	super::initializeListeners();
}

bool TutorialAVictory::tryHijackState(GameState* gameState)
{
	if (gameState->tutorialMode == StateOverride::TutorialMode::TutorialA)
	{
		this->initializeCallbacks(gameState);
		this->runTutorialLossDisplay(gameState);

		return true;
	}

	return false;
}

void TutorialAVictory::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void TutorialAVictory::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void TutorialAVictory::initializeCallbacks(GameState* gameState)
{
	this->lossDisplayNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialAVictory::runTutorialLossDisplay(GameState* gameState)
{
	this->lossDisplayNextButton->enableInteraction(0);
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 255));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowLossDisplay->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->lossesDisplayPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAVictory::concludeTutorial(GameState* gameState)
{
	this->lossDisplayNextButton->disableInteraction();
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 0));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowLossDisplay->hidePointer();
	this->focusTakeOver->unfocus();

	this->unHijackState(gameState);
}
