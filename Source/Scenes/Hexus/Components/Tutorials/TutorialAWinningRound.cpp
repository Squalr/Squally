#include "TutorialAWinningRound.h"

TutorialAWinningRound* TutorialAWinningRound::create()
{
	TutorialAWinningRound* instance = new TutorialAWinningRound();

	instance->autorelease();

	return instance;
}

TutorialAWinningRound::TutorialAWinningRound()
{
	this->focusTakeOver = FocusTakeOver::create();
	this->scoreTotalsTutorialLabel = Label::create("Nice! Now your score is higher than your opponents!",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(420.0f, 0.0f)
	);
	this->helpArrowScoreTotals = HelpArrow::create();

	Label* scoreTotalsNextLabel = Label::create("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* scoreTotalsNextLabelSelected = Label::create("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	scoreTotalsNextLabel->enableOutline(Color4B::BLACK, 2);
	scoreTotalsNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->scoreTotalsNextButton = TextMenuSprite::create(scoreTotalsNextLabel, scoreTotalsNextLabelSelected, Sprite::create(Resources::Minigames_Hexus_ButtonPlank), Sprite::create(Resources::Minigames_Hexus_ButtonPlankHover));

	this->scoreTotalsTutorialLabel->enableOutline(Color4B::BLACK, 2);
	this->scoreTotalsTutorialLabel->setAnchorPoint(Vec2(0.5f, 0.0f));
	this->helpArrowScoreTotals->setRotation(-90.0f);

	this->addChild(this->focusTakeOver);
	this->addChild(this->scoreTotalsTutorialLabel);
	this->addChild(this->scoreTotalsNextButton);
	this->addChild(this->helpArrowScoreTotals);
}

TutorialAWinningRound::~TutorialAWinningRound()
{
}

void TutorialAWinningRound::onEnter()
{
	TutorialBase::onEnter();

	this->scoreTotalsTutorialLabel->setOpacity(0);

	this->scoreTotalsNextButton->disableInteraction(0);
}

void TutorialAWinningRound::initializePositions()
{
	TutorialBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->scoreTotalsTutorialLabel->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f + 32.0f);
	this->scoreTotalsNextButton->setPosition(visibleSize.width / 2.0f - 256.0f, visibleSize.height / 2.0f - 32.0f);
	this->helpArrowScoreTotals->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::totalAttackOffsetX - 144.0f, visibleSize.height / 2.0f - Config::totalAttackOffsetY));
}

void TutorialAWinningRound::initializeListeners()
{
	TutorialBase::initializeListeners();
}

bool TutorialAWinningRound::tryHijackState(GameState* gameState)
{
	if (gameState->tutorialMode == StateOverride::TutorialMode::TutorialA && gameState->stateType == GameState::StateType::TurnEnd && gameState->getPlayerTotal() > gameState->getEnemyTotal())
	{
		this->initializeCallbacks(gameState);
		this->runTutorialScoreTotal(gameState);

		return true;
	}

	return false;
}

void TutorialAWinningRound::onBeforeStateChange(GameState* gameState)
{
	TutorialBase::onBeforeStateChange(gameState);
}

void TutorialAWinningRound::onAnyStateChange(GameState* gameState)
{
	TutorialBase::onAnyStateChange(gameState);
}

void TutorialAWinningRound::initializeCallbacks(GameState* gameState)
{
	this->scoreTotalsNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
	{
		this->concludeTutorial(gameState);
	});
}

void TutorialAWinningRound::runTutorialScoreTotal(GameState* gameState)
{
	this->scoreTotalsNextButton->enableInteraction(0);
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 255));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 255));
	this->helpArrowScoreTotals->showPointer();

	std::vector<Node*> focusTargets = std::vector<Node*>();
	focusTargets.push_back(gameState->scoreTotalPointer);
	this->focusTakeOver->focus(focusTargets);
}

void TutorialAWinningRound::concludeTutorial(GameState* gameState)
{
	this->scoreTotalsNextButton->disableInteraction();
	this->scoreTotalsNextButton->runAction(FadeTo::create(0.25f, 0));
	this->scoreTotalsTutorialLabel->runAction(FadeTo::create(0.25f, 0));
	this->helpArrowScoreTotals->hidePointer();
	this->focusTakeOver->unfocus();
	gameState->updateState(gameState, GameState::StateType::TurnEnd);
}
