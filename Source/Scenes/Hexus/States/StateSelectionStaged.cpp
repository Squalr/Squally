#include "StateSelectionStaged.h"

StateSelectionStaged* StateSelectionStaged::create()
{
	StateSelectionStaged* instance = new StateSelectionStaged();

	instance->autorelease();

	return instance;
}

StateSelectionStaged::StateSelectionStaged() : StateBase(GameState::StateType::SelectionStaged)
{
	this->selectionLabel = Label::create("", Localization::getMainFont(), 28.0f);

	this->selectionLabel->setAnchorPoint(Vec2(0.0f, 1.0f));
	this->selectionLabel->setTextColor(Color4B::WHITE);
	this->selectionLabel->enableOutline(Color4B::BLACK, 2);
	this->selectionLabel->setDimensions(Config::statusLabelWidth - 48.0f, 0.0f);
	this->selectionLabel->setOpacity(0);

	this->cancelButton = MenuSprite::create(Resources::Menus_Buttons_CancelV2Button, Resources::Menus_Buttons_CancelV2ButtonHover, Resources::Menus_Buttons_CancelV2ButtonClick);
	this->cancelButton->setCascadeOpacityEnabled(true);
	this->cancelButton->setOpacity(0.0f);
	this->cancelButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->helpButton = MenuSprite::create(Resources::Menus_Buttons_GraphV2Button, Resources::Menus_Buttons_GraphV2ButtonHover, Resources::Menus_Buttons_GraphV2ButtonClick);
	this->helpButton->setCascadeOpacityEnabled(true);
	this->helpButton->setOpacity(0.0f);
	this->helpButton->setAnchorPoint(Vec2(0.0f, 1.0f));

	this->addChild(this->selectionLabel);
	this->addChild(this->cancelButton);
	this->addChild(this->helpButton);
}

StateSelectionStaged::~StateSelectionStaged()
{
}

void StateSelectionStaged::initializePositions()
{
	StateBase::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->cancelButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->helpButton->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter + Config::statusLabelWidth / 2.0f + this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
	this->selectionLabel->setPosition(visibleSize.width / 2.0f + Config::rightColumnCenter - Config::statusLabelWidth / 2.0f - this->cancelButton->getContentSize().width / 2.0f, visibleSize.height / 2.0f + Config::statusLabelOffsetY);
}

void StateSelectionStaged::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateSelectionStaged::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);

	this->activeGameState = gameState;

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			break;
		case GameState::Turn::Enemy:
			this->aiPerformAction(gameState);
			break;
	}

	this->updateSelectionStatus();
}

void StateSelectionStaged::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateSelectionStaged::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	this->clearSelectionStatus();
}

void StateSelectionStaged::initializeCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(StateSelectionStaged::onSelectionCancel, this));
	this->helpButton->setClickCallback(CC_CALLBACK_1(StateSelectionStaged::onHelpClick, this));
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this));

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			break;
		case CardData::CardType::Decimal:
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			break;
		case CardData::CardType::Hexidecimal:
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			break;
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			gameState->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			gameState->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			gameState->enemyHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this));
			break;
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
			gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this));
			gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this));
			gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this));
			break;
	}
}

void StateSelectionStaged::selectCard(Card* card)
{
	if (card == nullptr || this->activeGameState->selectedCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == this->activeGameState->selectedCard)
	{
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));
		GameState::updateState(this->activeGameState, GameState::StateType::Neutral);
		this->activeGameState->selectedCard = nullptr;
	}
	else
	{
		// Otherwise this is just a selection/re-staging of a new card
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position));

		this->activeGameState->selectedCard = card;
		this->activeGameState->selectedCard->stopAllActions();
		this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

		// Transition to the same state (re-initialize things)
		GameState::updateState(this->activeGameState, GameState::StateType::SelectionStaged);
	}
}

void StateSelectionStaged::stageSelectedSacrificeCard(Card* card)
{
	if (this->activeGameState->selectedCard == nullptr)
	{
		return;
	}
}

void StateSelectionStaged::stageSelectedCombineCard(Card* card)
{
	if (this->activeGameState->selectedCard == nullptr)
	{
		return;
	}

	this->activeGameState->stagedCombineSourceCard = card;
	GameState::updateState(this->activeGameState, GameState::StateType::CombineStaged);
}

void StateSelectionStaged::playSelectedCard(CardRow* cardRow)
{
	if (this->activeGameState->selectedCard == nullptr)
	{
		return;
	}

	switch (this->activeGameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerBinaryCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
			break;
		}
		case CardData::CardType::Decimal:
		{
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerDecimalCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerHexCards->insertCard(this->activeGameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
			break;
		}
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
		{
			this->activeGameState->playerHand->removeCard(this->activeGameState->selectedCard);
			this->activeGameState->playerGraveyard->insertCardTop(this->activeGameState->selectedCard, true, Config::insertDelay);

			Card::Operation operation = Card::toOperation(this->activeGameState->selectedCard->cardData->cardType, 0);

			for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
			{
				Card* card = *it;

				card->addOperation(operation);
			}

			SoundManager::playSoundResource(Resources::Sounds_Hexus_Attacks_Card_Game_Abilities_Air_Glitter_01);
			GameState::updateState(this->activeGameState, GameState::StateType::TurnEnd);
			break;
		}
		default:
			break;
	}

	this->activeGameState->selectedCard = nullptr;
}

void StateSelectionStaged::aiPerformAction(GameState* gameState)
{
	Card* selectedCard = this->activeGameState->selectedCard;

	if (selectedCard != nullptr)
	{
		std::vector<CardRow *> rows = gameState->getAllRows();
		switch (selectedCard->cardData->cardType)
		{
			case CardData::CardType::Binary:
			{
				gameState->enemyHand->removeCard(selectedCard);
				gameState->enemyBinaryCards->insertCard(selectedCard, Config::insertDelay);
				SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
				break;
			}
			case CardData::CardType::Decimal:
			{
				gameState->enemyHand->removeCard(selectedCard);
				gameState->enemyDecimalCards->insertCard(selectedCard, Config::insertDelay);
				SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
				break;
			}
			case CardData::CardType::Hexidecimal:
			{
				gameState->enemyHand->removeCard(selectedCard);
				gameState->enemyHexCards->insertCard(selectedCard, Config::insertDelay);
				SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
				break;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_INV:
			{
				Card::Operation operation = Card::toOperation(selectedCard->cardData->cardType, 0);

				// Apply the card
				for (auto it = gameState->stagedCombineCardRow->rowCards->begin(); it != gameState->stagedCombineCardRow->rowCards->end(); it++)
				{
					Card* card = *it;
					card->addOperation(operation);
				}

				gameState->enemyHand->removeCard(selectedCard);
				gameState->enemyGraveyard->insertCardTop(selectedCard, true, Config::insertDelay);
				SoundManager::playSoundResource(Resources::Sounds_Hexus_Attacks_Card_Game_Abilities_Air_Glitter_01);
			}
			default:
				break;
		}
	}

	GameState::updateState(gameState, GameState::StateType::TurnEnd);
}

void StateSelectionStaged::onSelectionCancel(MenuSprite* menuSprite)
{
	this->selectCard(this->activeGameState->selectedCard);
}

void StateSelectionStaged::onHelpClick(MenuSprite* menuSprite)
{
	// TODO: Show help menu for the type
	switch (this->activeGameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
			break;
		case CardData::CardType::Decimal:
			break;
		case CardData::CardType::Hexidecimal:
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

void StateSelectionStaged::updateSelectionStatus()
{
	if (this->activeGameState->turn == GameState::Turn::Player && this->activeGameState->selectedCard != nullptr)
	{
		switch (this->activeGameState->selectedCard->cardData->cardType)
		{
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB:
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
			case CardData::CardType::Special_INV:
			default:
				this->selectionLabel->setString("Choose a row to play the card");
				break;
		}

		this->selectionLabel->runAction(FadeTo::create(0.25f, 255));
		this->cancelButton->runAction(FadeTo::create(0.25f, 255));
		this->helpButton->runAction(FadeTo::create(0.25f, 255));
	}
	else
	{
		this->clearSelectionStatus();
	}
}

void StateSelectionStaged::clearSelectionStatus()
{
	this->selectionLabel->runAction(FadeTo::create(0.25f, 0));
	this->cancelButton->runAction(FadeTo::create(0.25f, 0));
	this->helpButton->runAction(FadeTo::create(0.25f, 0));
}
