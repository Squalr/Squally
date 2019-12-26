#include "SarudeTutorialClaimVictory.h"

#include <vector>

#include "cocos/2d/CCActionInterval.h"
#include "cocos/base/CCDirector.h"

#include "Engine/Input/ClickableTextNode.h"
#include "Engine/Localization/LocalizedLabel.h"
#include "Engine/UI/Controls/HelpArrow.h"
#include "Engine/UI/HUD/FocusTakeOver.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/StateOverride.h"

#include "Resources/UIResources.h"

#include "Strings/Strings.h"

using namespace cocos2d;

SarudeTutorialClaimVictory* SarudeTutorialClaimVictory::create()
{
	SarudeTutorialClaimVictory* instance = new SarudeTutorialClaimVictory();

	instance->autorelease();

	return instance;
}

SarudeTutorialClaimVictory::SarudeTutorialClaimVictory() : super(GameState::StateType::Neutral)
{
	this->focusTakeOver = FocusTakeOver::create();
	this->claimVictoryLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::P, Strings::Hexus_Tutorials_Sarude_ClaimWin::create(), Size(640.0f, 0.0f), TextHAlignment::CENTER);
	this->helpArrowHandCards = HelpArrow::create();

	LocalizedLabel* tutorialNextLabel = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());
	LocalizedLabel* tutorialNextLabelSelected = LocalizedLabel::create(LocalizedLabel::FontStyle::Main, LocalizedLabel::FontSize::H3, Strings::Menus_GotIt::create());

	tutorialNextLabel->enableOutline(Color4B::BLACK, 2);
	tutorialNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->tutorialNextButton = ClickableTextNode::create(tutorialNextLabel, tutorialNextLabelSelected, Sprite::create(UIResources::Menus_Buttons_WoodButton), Sprite::create(UIResources::Menus_Buttons_WoodButtonSelected));

	this->claimVictoryLabel->enableOutline(Color4B::BLACK, 2);
	this->claimVictoryLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpArrowHandCards->setRotation(0.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->claimVictoryLabel);
	this->addChild(this->tutorialNextButton);
	this->addChild(this->helpArrowHandCards);
}

SarudeTutorialClaimVictory::~SarudeTutorialClaimVictory()
{
}

void SarudeTutorialClaimVictory::onEnter()
{
	super::onEnter();

	this->claimVictoryLabel->setOpacity(0);

	this->tutorialNextButton->disableInteraction(0);
}

void SarudeTutorialClaimVictory::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->claimVictoryLabel->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 80.0f);
	this->tutorialNextButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f - 144.0f);
	this->helpArrowHandCards->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f - 288.0f));
}

void SarudeTutorialClaimVictory::initializeListeners()
{
	super::initializeListeners();
}

bool SarudeTutorialClaimVictory::tryHijackState(GameState* gameState)
{
	if (gameState->enemyPassed && gameState->getPlayerTotal() > gameState->getEnemyTotal())
	{
		this->initializeCallbacks(gameState);
		this->runTutorialHandCards(gameState);

		return true;
	}

	return false;
}

void SarudeTutorialClaimVictory::onBeforeStateChange(GameState* gameState)
{
	super::onBeforeStateChange(gameState);
}

void SarudeTutorialClaimVictory::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void SarudeTutorialClaimVictory::initializeCallbacks(GameState* gameState)
{
	this->tutorialNextButton->setMouseClickCallback([=](InputEvents::MouseEventArgs* args)
	{
		this->tryUnHijackState(gameState);
	});
}

void SarudeTutorialClaimVictory::runTutorialHandCards(GameState* gameState)
{
	this->tutorialNextButton->enableInteraction(0);
	this->tutorialNextButton->runAction(FadeTo::create(0.25f, 255));
	this->claimVictoryLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowHandCards->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->claimVictoryButtonPointer);
	this->focusTakeOver->focus(focusTargets);
}

void SarudeTutorialClaimVictory::unHijackState(GameState* gameState)
{
	this->tutorialNextButton->disableInteraction();
	this->tutorialNextButton->runAction(FadeTo::create(0.25f, 0));
	this->claimVictoryLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowHandCards->hidePointer();

	this->focusTakeOver->unfocus();
}
