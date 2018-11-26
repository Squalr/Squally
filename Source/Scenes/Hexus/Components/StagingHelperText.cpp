#include "StagingHelperText.h"

StagingHelperText* StagingHelperText::create()
{
	StagingHelperText* instance = new StagingHelperText();

	instance->autorelease();

	return instance;
}

StagingHelperText::StagingHelperText()
{
	this->selectionLabel = Label::create("", Localization::getMainFont(), Localization::getFontSizeP(Localization::getMainFont()));

	this->selectionLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->selectionLabel->setTextColor(Color4B::WHITE);
	this->selectionLabel->enableOutline(Color4B::BLACK, 2);
	this->selectionLabel->setDimensions(Config::statusLabelWidth - 48.0f, 0.0f);

	this->cancelButton = MenuSprite::create(UIResources::Menus_Buttons_CancelV2Button, UIResources::Menus_Buttons_CancelV2ButtonHover);
	this->cancelButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->helpButton = MenuSprite::create(UIResources::Menus_Buttons_GraphV2Button, UIResources::Menus_Buttons_GraphV2ButtonHover);
	this->helpButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->selectionLabel);
	this->addChild(this->cancelButton);
	this->addChild(this->helpButton);
}

StagingHelperText::~StagingHelperText()
{
}

void StagingHelperText::onEnter()
{
	ComponentBase::onEnter();

	this->selectionLabel->setOpacity(0);
	this->cancelButton->setOpacity(0.0f);
	this->helpButton->setOpacity(0.0f);
}

void StagingHelperText::initializePositions()
{
	ComponentBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cancelButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->helpButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f + this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->selectionLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter - Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
}

void StagingHelperText::onBeforeStateChange(GameState* gameState)
{
	ComponentBase::onBeforeStateChange(gameState);
}

void StagingHelperText::onAnyStateChange(GameState* gameState)
{
	ComponentBase::onAnyStateChange(gameState);

	switch (gameState->stateType)
	{
		case GameState::StateType::SelectionStaged:
		{
			this->updateSelectionStatus(gameState);
			this->cancelButton->setClickCallback(CC_CALLBACK_1(StagingHelperText::onSelectionCancel, this, gameState));
			this->helpButton->setClickCallback(CC_CALLBACK_1(StagingHelperText::onHelpClick, this, gameState));
			break;
		}
		case GameState::StateType::CombineStaged:
		{
			this->updateCombineStatus(gameState);
			this->cancelButton->setClickCallback(CC_CALLBACK_1(StagingHelperText::onCombineCancel, this, gameState));
			this->helpButton->setClickCallback(CC_CALLBACK_1(StagingHelperText::onHelpClick, this, gameState));
			break;
		}
		default:
		{
			this->clearSelectionStatus();
			break;
		}
	}
}

void StagingHelperText::onSelectionCancel(MenuSprite* menuSprite, GameState* gameState)
{
	if (gameState->selectedHandCard != nullptr)
	{
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));
		gameState->selectedHandCard = nullptr;
	}

	GameState::updateState(gameState, GameState::StateType::Neutral);
}

void StagingHelperText::updateCombineStatus(GameState* gameState)
{
	if (gameState->turn == GameState::Turn::Player && gameState->stateType == GameState::StateType::CombineStaged && gameState->selectedSourceCard == nullptr)
	{
		this->selectionLabel->setString("Choose the source card for your operation");
		this->selectionLabel->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
	else if (gameState->turn == GameState::Turn::Player && gameState->stateType == GameState::StateType::CombineStaged && gameState->selectedDestinationCard == nullptr)
	{
		this->selectionLabel->setString("Choose the target card for your operation");
		this->selectionLabel->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
	}
}

void StagingHelperText::updateSelectionStatus(GameState* gameState)
{
	if (gameState->turn == GameState::Turn::Player && gameState->selectedHandCard != nullptr)
	{
		switch (gameState->selectedHandCard->cardData->cardType)
		{
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
			case CardData::CardType::Special_INV:
				this->selectionLabel->setString("Choose a source card for the operation");
				break;
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal:
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			default:
				this->selectionLabel->setString("Choose a row to play the card");
				break;
		}

		this->selectionLabel->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->enableInteraction();
		// this->helpButton->runAction(FadeTo::create(0.25f, 255));
		// this->helpButton->enableInteraction();
	}
}

void StagingHelperText::clearSelectionStatus()
{
	this->selectionLabel->setString("");
	this->cancelButton->setClickCallback(nullptr);
	this->helpButton->setClickCallback(nullptr);
	this->selectionLabel->runAction(FadeTo::create(0.25f, 0));
	this->cancelButton->runAction(FadeTo::create(0.25f, 0));
	this->cancelButton->disableInteraction();
	this->helpButton->runAction(FadeTo::create(0.25f, 0));
	this->helpButton->disableInteraction();
}

void StagingHelperText::onCombineCancel(MenuSprite* menuSprite, GameState* gameState)
{
	if (gameState->selectedSourceCard != nullptr)
	{
		gameState->selectedSourceCard->stopAllActions();
		gameState->selectedSourceCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedSourceCard->position));
		gameState->selectedSourceCard = nullptr;
	}

	if (gameState->selectedHandCard != nullptr)
	{
		gameState->selectedHandCard->stopAllActions();
		gameState->selectedHandCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedHandCard->position));
		gameState->selectedHandCard = nullptr;
	}

	GameState::updateState(gameState, GameState::StateType::Neutral);
}

void StagingHelperText::onHelpClick(MenuSprite* menuSprite, GameState* gameState)
{
	// TODO: Show help menu for the type
	switch (gameState->selectedHandCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
			break;
		case CardData::CardType::Decimal:
			break;
		case CardData::CardType::Hexidecimal:
			break;
		case CardData::CardType::Special_MOV:
			break;
		case CardData::CardType::Special_AND:
			break;
		case CardData::CardType::Special_OR:
			break;
		case CardData::CardType::Special_XOR:
			break;
		case CardData::CardType::Special_ADD:
			break;
		case CardData::CardType::Special_SUB:
			break;
		case CardData::CardType::Special_SHL:
			break;
		case CardData::CardType::Special_SHR:
			break;
		case CardData::CardType::Special_FLIP1:
			break;
		case CardData::CardType::Special_FLIP2:
			break;
		case CardData::CardType::Special_FLIP3:
			break;
		case CardData::CardType::Special_FLIP4:
			break;
		case CardData::CardType::Special_INV:
			break;
		default:
			break;
	}
}
