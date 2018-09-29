#include "ControlGameEnd.h"

ControlGameEnd* ControlGameEnd::create()
{
	ControlGameEnd* instance = new ControlGameEnd();

	instance->autorelease();

	return instance;
}

ControlGameEnd::ControlGameEnd()
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

ControlGameEnd::~ControlGameEnd()
{
}

void ControlGameEnd::initializeListeners()
{
	ComponentBase::initializeListeners();
}

void ControlGameEnd::onBackClick(MenuSprite* menuSprite)
{
	this->activeGameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs(this->activeGameState->stateType == GameState::StateType::Win, this->activeGameState->opponentData));
}

void ControlGameEnd::initializePositions()
{
	ComponentBase::initializePositions();
	Size visibleSize = Director::getInstance()->getVisibleSize();
	this->backButton->setPosition(visibleSize.width / 2.0f + Config::centerColumnCenter, visibleSize.height / 2.0f);
}

void ControlGameEnd::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	switch (gameState->stateType)
	{
		case GameState::StateType::Lose:
		case GameState::StateType::Win:
			this->backButton->enableInteraction(0);
			this->backButton->runAction(FadeTo::create(Config::replaceEndButtonFadeSpeed, 255));
			this->backButton->setClickCallback(CC_CALLBACK_1(ControlGameEnd::onBackClick, this));
			break;
		default:
			this->backButton->disableInteraction(0);
			this->backButton->setClickCallback(nullptr);
			break;
	}
}
