#include "StateGameEnd.h"

#include "Resources/SoundResources.h"

StateGameEnd* StateGameEnd::create()
{
	StateGameEnd* instance = new StateGameEnd();

	instance->autorelease();

	return instance;
}

StateGameEnd::StateGameEnd() : StateBase(GameState::StateType::GameEnd)
{
	Label* backButtonLabel = Label::create("Leave", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Leave", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		UIResources::Menus_Buttons_WoodButton,
		UIResources::Menus_Buttons_WoodButtonSelected
	);

	this->backButton->setOpacity(0);

	this->addChild(this->backButton);
}

StateGameEnd::~StateGameEnd()
{
}

void StateGameEnd::onEnter()
{
	StateBase::onEnter();

	this->backButton->setOpacity(0);
}

void StateGameEnd::initializeListeners()
{
	StateBase::initializeListeners();
}

void StateGameEnd::initializePositions()
{
	StateBase::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void StateGameEnd::onBackClick(MenuSprite* menuSprite, GameState* gameState)
{
	GameState::updateState(gameState, GameState::StateType::EmptyState);

	if (gameState->playerLosses >= 2 && gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Reward);
		gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(HexusEvents::HexusGameResult::Draw, gameState->opponentData, gameState->gameDurationInSeconds));
	}
	else if (gameState->playerLosses < 2 && gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Reward);
		gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(HexusEvents::HexusGameResult::PlayerWon, gameState->opponentData, gameState->gameDurationInSeconds));
	}
	else
	{
		gameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(HexusEvents::HexusGameResult::EnemyWon, gameState->opponentData, gameState->gameDurationInSeconds));
	}
}

void StateGameEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateGameEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	if (gameState->playerLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Defeat);
	}
	else if (gameState->enemyLosses >= 2)
	{
		SoundManager::playSoundResource(SoundResources::Hexus_Victory);
	}

	this->backButton->enableInteraction(0);
	this->backButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));
	this->backButton->setClickCallback(CC_CALLBACK_1(StateGameEnd::onBackClick, this, gameState));
}

void StateGameEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateGameEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	this->backButton->disableInteraction(0);
	this->backButton->setClickCallback(nullptr);
}
