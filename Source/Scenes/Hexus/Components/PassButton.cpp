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

	this->addChild(this->passButton);
}

PassButton::~PassButton()
{
}

void PassButton::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->passButton->setPosition(visibleSize.width / 2.0f + Config::leftColumnCenter + Config::passButtonOffsetX, visibleSize.height / 2.0f + Config::passButtonOffsetY);
}

void PassButton::onStateChange(GameState* gameState)
{
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
	GameState::updateState(gameState, GameState::StateType::EmptyState); // TODO
}
