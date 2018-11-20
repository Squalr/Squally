#include "TutorialAVictory.h"

TutorialAVictory* TutorialAVictory::create()
{
	TutorialAVictory* instance = new TutorialAVictory();

	instance->autorelease();

	return instance;
}

TutorialAVictory::TutorialAVictory()
{
	this->focusTakeOver = FocusTakeOver::create();
	this->lossDisplayTutorialLabel = Label::create("Nice! Your opponent has lost 2 lives, so you win the match!",
		Localization::getMainFont(),
		Localization::getFontSizeP(Localization::getMainFont()),
		Size(420.0f, 0.0f)
	);
	this->helpArrowLossDisplay = HelpArrow::create();

	Label* lossesDisplayNextLabel = Label::create("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* lossesDisplayNextLabelSelected = Label::create("Next", Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	lossesDisplayNextLabel->enableOutline(Color4B::BLACK, 2);
	lossesDisplayNextLabelSelected->enableOutline(Color4B::BLACK, 2);

	this->lossDisplayNextButton = TextMenuSprite::create(lossesDisplayNextLabel, lossesDisplayNextLabelSelected, Sprite::create(Resources::Minigames_Hexus_ButtonPlank), Sprite::create(Resources::Minigames_Hexus_ButtonPlankHover));

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
	TutorialBase::onEnter();

	this->lossDisplayTutorialLabel->setOpacity(0);
	this->lossDisplayNextButton->disableInteraction(0);
}

void TutorialAVictory::initializePositions()
{
	TutorialBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->lossDisplayTutorialLabel->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f + 32.0f);
	this->lossDisplayNextButton->setPosition(visibleSize.width / 2.0f - 420.0f, visibleSize.height / 2.0f - 32.0f);
	this->helpArrowLossDisplay->setPosition(Vec2(visibleSize.width / 2.0f + Config::leftColumnCenter + (Config::socketAOffsetX + Config::socketBOffsetX) / 2.0f, visibleSize.height / 2.0f + Config::socketOffsetY + 128.0f));
}

void TutorialAVictory::initializeListeners()
{
	TutorialBase::initializeListeners();
}

bool TutorialAVictory::tryHijackState(GameState* gameState)
{
	if (gameState->tutorialMode == StateOverride::TutorialMode::TutorialA && gameState->stateType == GameState::StateType::GameEnd)
	{
		this->initializeCallbacks(gameState);
		this->runTutorialLossDisplay(gameState);

		return true;
	}

	return false;
}

void TutorialAVictory::onBeforeStateChange(GameState* gameState)
{
	TutorialBase::onBeforeStateChange(gameState);
}

void TutorialAVictory::onAnyStateChange(GameState* gameState)
{
	TutorialBase::onAnyStateChange(gameState);
}

void TutorialAVictory::initializeCallbacks(GameState* gameState)
{
	this->lossDisplayNextButton->setClickCallback([=](MenuSprite* menuSprite, MouseEvents::MouseEventArgs* args)
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
	gameState->updateState(gameState, GameState::StateType::RoundEnd);
}
