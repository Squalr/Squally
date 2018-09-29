#include "PassButton.h"

const std::string PassButton::StringKeyHexusPass = "Menu_Hexus_Pass";

PassButton* PassButton::create()
{
	PassButton* instance = new PassButton();

	instance->autorelease();

	return instance;
}

PassButton::PassButton()
{
	Label* passLabel = Label::create(Localization::resolveString(PassButton::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* passLabelHover = Label::create(Localization::resolveString(PassButton::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));
	Label* passLabelClick = Label::create(Localization::resolveString(PassButton::StringKeyHexusPass), Localization::getMainFont(), Localization::getFontSizeH3(Localization::getMainFont()));

	this->passButton = TextMenuSprite::create(
		passLabel,
		passLabelHover,
		passLabelClick,
		Resources::Minigames_Hexus_Button,
		Resources::Minigames_Hexus_ButtonHover,
		Resources::Minigames_Hexus_ButtonClick);
	this->passButton->setClickSound(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);

	this->playerPassIndicator = Sprite::create(Resources::Minigames_Hexus_Flags);
	this->playerPassIndicator->setOpacity(0);
	this->enemyPassIndicator = Sprite::create(Resources::Minigames_Hexus_Flags);
	this->enemyPassIndicator->setOpacity(0);
	
	this->addChild(this->passButton);
	this->addChild(this->playerPassIndicator);
	this->addChild(this->enemyPassIndicator);
}

PassButton::~PassButton()
{
}

void PassButton::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->passButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
	this->playerPassIndicator->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::playerPassIndicatorOffsetX, visibleSize.height / 2.0f + Config::playerPassIndicatorOffsetY);
	this->enemyPassIndicator->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::enemyPassIndicatorOffsetX, visibleSize.height / 2.0f + Config::enemyPassIndicatorOffsetY);
}

void PassButton::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (this->activeGameState->playerPass) {
		this->playerPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 255));
	} else {
		this->playerPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 0));
	}

	if (this->activeGameState->enemyPass) {
		this->enemyPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 255));
	} else {
		this->enemyPassIndicator->runAction(FadeTo::create(Config::passIndicatorFadeSpeed, 0));
	}

	switch (gameState->stateType) {
	case GameState::StateType::ControlNeutral:
		this->passButton->setClickCallback(CC_CALLBACK_1(PassButton::onPassClick, this, gameState));
		this->passButton->enableInteraction();
		break;
	default:
		this->passButton->disableInteraction();
		this->passButton->setClickCallback(nullptr);
		break;
	}
}

void PassButton::onPassClick(MenuSprite* menuSprite, GameState* gameState)
{
	gameState->playerPass = true;
	GameState::updateState(gameState, GameState::StateType::EndTurn);
}
