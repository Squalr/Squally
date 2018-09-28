#include "ControlGameEnd.h"

ControlGameEnd* ControlGameEnd::create()
{
	ControlGameEnd* instance = new ControlGameEnd();

	instance->autorelease();

	return instance;
}

ControlGameEnd::ControlGameEnd()
{
	Label* backButtonLabel = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelHover = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));
	Label* backButtonLabelClick = Label::create("Back", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	backButtonLabel->enableOutline(Color4B::BLACK, 2);
	backButtonLabelHover->enableOutline(Color4B::BLACK, 2);
	backButtonLabelClick->enableOutline(Color4B::BLACK, 2);

	this->backButton = TextMenuSprite::create(
		backButtonLabel,
		backButtonLabelHover,
		backButtonLabelClick,
		Resources::Menus_Buttons_GenericButton,
		Resources::Menus_Buttons_GenericButtonHover,
		Resources::Menus_Buttons_GenericButtonClick
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
	this->backButton->setClickCallback(CC_CALLBACK_1(ControlGameEnd::onBackClick, this));
}

void ControlGameEnd::onBackClick(MenuSprite* menuSprite)
{
	this->activeGameState->onGameEndCallback(HexusEvents::HexusGameResultEventArgs((this->activeGameState->playerLosses < 2), this->activeGameState->opponentData));

	NavigationEvents::navigateBack();
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
		break;
	default:
		this->backButton->disableInteraction(0);
		break;
	}
}
