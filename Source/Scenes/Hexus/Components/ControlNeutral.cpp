#include "ControlNeutral.h"

ControlNeutral* ControlNeutral::create()
{
	ControlNeutral* instance = new ControlNeutral();

	instance->autorelease();

	return instance;
}

ControlNeutral::ControlNeutral()
{
}

ControlNeutral::~ControlNeutral()
{
}

void ControlNeutral::onStateChange(GameState* gameState)
{
	this->activeGameState = gameState;

	if (gameState->stateType == GameState::StateType::ControlNeutral) {
		switch (gameState->turn)
		{
		case GameState::Turn::Player:
			this->initializeCallbacks(gameState);
			this->activeGameState->playerHand->enableRowCardInteraction();
			break;
		case GameState::Turn::Enemy:
			this->aiDoSelection(gameState);
			this->activeGameState->playerHand->disableRowCardInteraction();
			break;
		}
	}
}

void ControlNeutral::initializeCallbacks(GameState* gameState)
{
	gameState->playerHand->setMouseClickCallback(CC_CALLBACK_1(ControlNeutral::selectCard, this));
	gameState->enemyHand->setMouseClickCallback(CC_CALLBACK_1(ControlNeutral::selectCard, this));
}

void ControlNeutral::selectCard(Card* card)
{
	this->activeGameState->selectedCard = card;
	this->activeGameState->selectedCard->stopAllActions();
	this->activeGameState->selectedCard->runAction(MoveTo::create(Config::cardSelectSpeed, this->activeGameState->selectedCard->position + Vec2(0.0f, Config::cardSelectOffsetY)));

	GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
}

void ControlNeutral::aiDoSelection(GameState* gameState)
{
	this->activeGameState->selectedCard = nullptr;

	int passIfDiffAbove = 30; // Give up if player is too far ahead
	if (gameState->enemyLosses < 1 && gameState->getPlayerTotal() > gameState->getEnemyTotal() + passIfDiffAbove) {
		gameState->enemyPass = true;
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	}

	// If it's not the last round we better save some cards
	int cardsToSaveForLastRound = 4;
	if (gameState->enemyLosses < 1 && gameState->enemyHand->rowCards->size() <= cardsToSaveForLastRound) {
		gameState->enemyPass = true;
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	} 
	
	// If the player passes and we're ahead we won, so pass
	if (gameState->playerPass && gameState->enemyIsWinning()) {
		gameState->enemyPass = true;
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	} 

	// Otherwise 
	for (auto it = gameState->enemyHand->rowCards->begin(); it != gameState->enemyHand->rowCards->end(); it++)
	{
		Card* card = *it;
		std::vector<CardRow *> rows = gameState->getAllRows();

		switch (card->cardData->cardType)
		{
			case CardData::CardType::Binary:
			case CardData::CardType::Decimal:
			case CardData::CardType::Hexidecimal: {
				this->activeGameState->selectedCard = card;
				GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
				return;
			}
			case CardData::CardType::Special_SHL:
			case CardData::CardType::Special_SHR:
			case CardData::CardType::Special_FLIP1:
			case CardData::CardType::Special_FLIP2:
			case CardData::CardType::Special_FLIP3:
			case CardData::CardType::Special_FLIP4:
			case CardData::CardType::Special_INV: {
				// don't play this card if there are no viable moves
				Card::Operation operation = Card::toOperation(card->cardData->cardType, 0);
				for (auto it = rows.begin(); it != rows.end(); it++)
				{
					CardRow* row = *it;
					int diff = row->simulateCardEffect(card) * (row->isPlayerRow() ? -1 : 1);
					if (diff > 1) {
						this->activeGameState->selectedCard = card;
						GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
						return;
					}
				}
				break;
			}
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB: 
			{
				// don't play this card if there are no viable moves
				if (gameState->getEnemyCardCount() > 1) {
					this->activeGameState->selectedCard = card;
					GameState::updateState(this->activeGameState, GameState::StateType::ControlCombineStaged);
					return;
				}
			}
			default: 
				break;
		}
	}

	// Unable to find a playable move, so pass
	this->activeGameState->enemyPass = true;
	GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
}
