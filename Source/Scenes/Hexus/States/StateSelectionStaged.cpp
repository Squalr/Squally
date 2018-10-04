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

	gameState->playerHand->enableRowCardInteraction();

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		case GameState::Turn::Enemy:
			this->aiPerformAction(gameState);
			break;
		default:
			break;
	}

	this->updateSelectionStatus(gameState);
}

void StateSelectionStaged::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);

	switch (gameState->turn)
	{
		case GameState::Turn::Player:
			this->initializeSelectablesAndCallbacks(gameState);
			break;
		case GameState::Turn::Enemy:
			break;
		default:
			break;
	}
}

void StateSelectionStaged::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);

	this->clearSelectionStatus();
}

void StateSelectionStaged::initializeSelectablesAndCallbacks(GameState* gameState)
{
	this->cancelButton->setClickCallback(CC_CALLBACK_1(StateSelectionStaged::onSelectionCancel, this, gameState));
	this->helpButton->setClickCallback(CC_CALLBACK_1(StateSelectionStaged::onHelpClick, this, gameState));

	gameState->playerHand->enableRowCardInteraction();
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(StateSelectionStaged::selectCard, this, gameState));

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			break;
		case CardData::CardType::Decimal:
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			break;
		case CardData::CardType::Hexidecimal:
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			break;
		case CardData::CardType::Special_SHL:
		case CardData::CardType::Special_SHR:
		case CardData::CardType::Special_FLIP1:
		case CardData::CardType::Special_FLIP2:
		case CardData::CardType::Special_FLIP3:
		case CardData::CardType::Special_FLIP4:
		case CardData::CardType::Special_INV:
			gameState->playerBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			gameState->playerDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			gameState->playerHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			gameState->enemyBinaryCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			gameState->enemyDecimalCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			gameState->enemyHexCards->enableRowSelection(CC_CALLBACK_1(StateSelectionStaged::playSelectedCard, this, gameState));
			break;
		case CardData::CardType::Special_AND:
		case CardData::CardType::Special_OR:
		case CardData::CardType::Special_XOR:
		case CardData::CardType::Special_ADD:
		case CardData::CardType::Special_SUB:
			gameState->playerBinaryCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerDecimalCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			gameState->playerHexCards->enableRowCardSelection(CC_CALLBACK_1(StateSelectionStaged::stageSelectedCombineCard, this, gameState));
			break;
	}
}

void StateSelectionStaged::selectCard(Card* card, GameState* gameState)
{
	if (card == nullptr || gameState->selectedCard == nullptr)
	{
		return;
	}

	// Unstage/deselect card if clicking the active card
	if (card == gameState->selectedCard)
	{
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));
		GameState::updateState(gameState, GameState::StateType::Neutral);
		gameState->selectedCard = nullptr;
	}
	else
	{
		// Otherwise this is just a selection/re-staging of a new card
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position));

		gameState->selectedCard = card;
		gameState->selectedCard->stopAllActions();
		gameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, gameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

		// Transition to the same state (re-initialize things)
		GameState::updateState(gameState, GameState::StateType::SelectionStaged);
	}
}

void StateSelectionStaged::stageSelectedCombineCard(Card* card, GameState* gameState)
{
	if (gameState->selectedCard == nullptr)
	{
		return;
	}

	gameState->stagedCombineSourceCard = card;
	GameState::updateState(gameState, GameState::StateType::CombineStaged);
}

void StateSelectionStaged::playSelectedCard(CardRow* cardRow, GameState* gameState)
{
	if (gameState->selectedCard == nullptr)
	{
		return;
	}

	switch (gameState->selectedCard->cardData->cardType)
	{
		case CardData::CardType::Binary:
		{
			gameState->playerHand->removeCard(gameState->selectedCard);
			gameState->playerBinaryCards->insertCard(gameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
			break;
		}
		case CardData::CardType::Decimal:
		{
			gameState->playerHand->removeCard(gameState->selectedCard);
			gameState->playerDecimalCards->insertCard(gameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
			break;
		}
		case CardData::CardType::Hexidecimal:
		{
			gameState->playerHand->removeCard(gameState->selectedCard);
			gameState->playerHexCards->insertCard(gameState->selectedCard, Config::insertDelay);
			SoundManager::playSoundResource(Resources::Sounds_Hexus_Card_Game_Movement_Deal_Single_Small_01);
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
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
			gameState->playerHand->removeCard(gameState->selectedCard);
			gameState->playerGraveyard->insertCardTop(gameState->selectedCard, true, Config::insertDelay);

			Card::Operation operation = Card::toOperation(gameState->selectedCard->cardData->cardType, 0);

			for (auto it = cardRow->rowCards->begin(); it != cardRow->rowCards->end(); it++)
			{
				Card* card = *it;

				card->addOperation(operation);
			}

			SoundManager::playSoundResource(Resources::Sounds_Hexus_Attacks_Card_Game_Abilities_Air_Glitter_01);
			GameState::updateState(gameState, GameState::StateType::TurnEnd);
			break;
		}
		default:
			break;
	}

	gameState->selectedCard = nullptr;
}

void StateSelectionStaged::aiPerformAction(GameState* gameState)
{
	Card* selectedCard = gameState->selectedCard;

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

void StateSelectionStaged::onSelectionCancel(MenuSprite* menuSprite, GameState* gameState)
{
	this->selectCard(gameState->selectedCard, gameState);
}

void StateSelectionStaged::onHelpClick(MenuSprite* menuSprite, GameState* gameState)
{
	// TODO: Show help menu for the type
	switch (gameState->selectedCard->cardData->cardType)
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

void StateSelectionStaged::updateSelectionStatus(GameState* gameState)
{
	if (gameState->turn == GameState::Turn::Player && gameState->selectedCard != nullptr)
	{
		switch (gameState->selectedCard->cardData->cardType)
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
