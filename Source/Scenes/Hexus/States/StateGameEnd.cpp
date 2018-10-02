#include "StateGameEnd.h"

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
	Label* backButtonLabelClick = Label::create("Leave", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		backButtonLabelClick,
		Resources::Minigames_Hexus_ButtonPlank,
		Resources::Minigames_Hexus_ButtonPlankHover,
		Resources::Minigames_Hexus_ButtonPlankClick
	);
	this->backButton->setOpacity(0);

	this->addChild(this->backButton);
}

StateGameEnd::~StateGameEnd()
{
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

void StateGameEnd::onBackClick(MenuSprite* menuSprite)
{
	if (this->activeGameState->stateType == GameState::StateType::GameEnd) {
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_Validation_03);
		this->activeGameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(true, this->activeGameState->opponentData));
	}
	else {
		this->activeGameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(false, this->activeGameState->opponentData));
	}
}

void StateGameEnd::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateGameEnd::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->activeGameState = gameState;

	switch (gameState->stateType)
	{
		case GameState::StateType::GameEnd:
			this->backButton->enableInteraction(0);
			this->backButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));
			this->backButton->setClickCallback(CC_CALLBACK_1(StateGameEnd::onBackClick, this));
			break;
		default:
			this->backButton->disableInteraction(0);
			this->backButton->setClickCallback(nullptr);
			break;
	}
}

void StateGameEnd::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateGameEnd::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
