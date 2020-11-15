#include "SarudeTutorialIntroSequence.h"

#include <vector>

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/HexusConfig.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SarudeTutorialIntroSequence* SarudeTutorialIntroSequence::create()
{
	SarudeTutorialIntroSequence* instance = new SarudeTutorialIntroSequence();

	instance->autorelease();

	return instance;
}

SarudeTutorialIntroSequence::SarudeTutorialIntroSequence() : super(GameState::StateType::RoundStart)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->lossDisplayTutorialLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_Sarude_RealMatch::create(), Size(420.0f, 0.0f));
	this->helpArrowLossDisplay = HelpArrow::create();
	this->lossDisplayNextButton = this->createNextButton();

	this->lossDisplayTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->lossDisplayTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpArrowLossDisplay->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->lossDisplayTutorialLabel);
	this->addChild(this->lossDisplayNextButton);
	this->addChild(this->helpArrowLossDisplay);
}

SarudeTutorialIntroSequence::~SarudeTutorialIntroSequence()
{
}

void SarudeTutorialIntroSequence::onEnter()
{
	super::onEnter();

	this->lossDisplayTutorialLabel->setOpacity(0);
	this->lossDisplayNextButton->disableInteraction(0);
}

void SarudeTutorialIntroSequence::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->lossDisplayTutorialLabel->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f + 32.0f);
	this->lossDisplayNextButton->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 32.0f);
	this->helpArrowLossDisplay->setPosition(Vec2(visibleSize.width / 2.0f + HexusConfig::leftColumnCenter + (HexusConfig::socketAOffsetX + HexusConfig::socketBOffsetX) / 2.0f, visibleSize.height / 2.0f + HexusConfig::socketOffsetY + 128.0f));
}

void SarudeTutorialIntroSequence::initializeListeners()
{
	super::initializeListeners();
}

bool SarudeTutorialIntroSequence::tryHijackState(GameState* gameState)
{
	this->defer([=]()
	{
		this->initializeCallbacks(gameState);
		this->runTutorialLossDisplay(gameState);
	});

	return true;
}

void SarudeTutorialIntroSequence::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void SarudeTutorialIntroSequence::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void SarudeTutorialIntroSequence::initializeCallbacks(GameState* gameState)
{
	this->lossDisplayNextButton->setMouseClickCallback([=](MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});

	this->whenKeyPressed({ EventKeyboard::KeyCode::KEY_SPACE }, [=](KeyboardEventArgs* args)
	{
		this->lossDisplayNextButton->interact();
	});
}

void SarudeTutorialIntroSequence::runTutorialLossDisplay(GameState* gameState)
{
	this->lossDisplayNextButton->enableInteraction(0);
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 255));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowLossDisplay->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->lossesDisplayPointer);
	this->focusTakeOver->focus(focusTargets);
}

void SarudeTutorialIntroSequence::unHijackState(GameState* gameState)
{
	this->lossDisplayNextButton->disableInteraction();
	this->lossDisplayNextButton->runAction(FadeTo::create(0.25f, 0));
	this->lossDisplayTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowLossDisplay->hidePointer();
	this->focusTakeOver->unfocus();
}
