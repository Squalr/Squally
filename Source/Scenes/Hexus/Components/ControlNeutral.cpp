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
			if (gameState->playerHand->rowCards->size() == 0) {
				gameState->showPassBanner = true;
				gameState->playerPass = true;
				GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
				return;
			}
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

	if (gameState->enemyPass) {
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	}

	if (gameState->enemyHand->rowCards->size() == 0) {
		gameState->showPassBanner = true;
		gameState->enemyPass = true;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	}

	int passIfDiffAbove = 30; // Give up if player is too far ahead
	if (gameState->enemyLosses < 1 && gameState->getPlayerTotal() > gameState->getEnemyTotal() + passIfDiffAbove) {
		gameState->showPassBanner = true;
		gameState->enemyPass = true;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	}

	// If it's not the last round we better save some cards
	int cardsToSaveForLastRound = 4;
	if (gameState->enemyLosses < 1 && gameState->enemyHand->rowCards->size() <= cardsToSaveForLastRound) {
		gameState->showPassBanner = true;
		gameState->enemyPass = true;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
		GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
		return;
	} 
	
	// If the player passes and we're ahead we won, so pass
	if (gameState->playerPass && gameState->enemyIsWinning()) {
		gameState->showPassBanner = true;
		gameState->enemyPass = true;
		SoundManager::playSoundResource(Resources::Sounds_Hexus_UI_CCG_NextPlayer4);
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
			case CardData::CardType::Special_INV:
			{
				// Calculate the best row to apply the card to
				CardRow* bestRow = nullptr;
				int bestDiff = INT_MIN;

				for (auto it = rows.begin(); it != rows.end(); it++)
				{
					CardRow* row = *it;
					int diff = row->isEmpty() ? 0 : (row->simulateCardEffect(card) * (row->isPlayerRow() ? -1 : 1));

					if (diff >= bestDiff)
					{
						bestDiff = diff;
						bestRow = row;
					}
				}

				if (bestDiff > 0)
				{
					this->activeGameState->selectedCard = card;
					this->activeGameState->stagedCombineCardRow = bestRow;
					GameState::updateState(this->activeGameState, GameState::StateType::ControlSelectionStaged);
					return;
				}
				
				break;
			}
			case CardData::CardType::Special_AND:
			case CardData::CardType::Special_OR:
			case CardData::CardType::Special_XOR:
			case CardData::CardType::Special_ADD:
			case CardData::CardType::Special_SUB: 
			{
				// n^2 card compare to figure out the best strategy
				// Maybe there is some better way to do this calculation

				std::vector<Card*> cards = gameState->getEnemyCards(); // all valid source cards for the operation must be our own
				Card* bestSourceCard = nullptr;
				Card* bestTargetCard = nullptr;
				int bestDiff = INT_MIN;

				// First simulate buffing your own cards
				for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
				{
					Card* sourceCard = *sourceCardIterator;

					// First we iterate through only our own cards
					for (auto targetCardIterator = cards.begin(); targetCardIterator != cards.end(); targetCardIterator++)
					{
						Card* targetCard = *targetCardIterator;
						if (sourceCard == targetCard) {
							continue; // we're not allowed to apply a card to itself
						}

						Card::Operation operation = Card::toOperation(
							card->cardData->cardType, 
							sourceCard->getAttack()
						);

						int before = targetCard->getAttack();
						int after = targetCard->simulateOperation(operation);
						int diff = (after - before);
						if (diff > bestDiff) {
							bestDiff = diff;
							bestSourceCard = sourceCard;
							bestTargetCard = targetCard;
						}
					}
				}

				// Then simulate attacking the player
				std::vector<Card*> playerCards = gameState->getPlayerCards();
				for (auto sourceCardIterator = cards.begin(); sourceCardIterator != cards.end(); sourceCardIterator++)
				{
					Card* sourceCard = *sourceCardIterator;

					// This time we iterate through the players cards
					for (auto targetCardIterator = playerCards.begin(); targetCardIterator != playerCards.end(); targetCardIterator++)
					{
						Card* targetCard = *targetCardIterator;

						if (sourceCard == targetCard) {
							continue; // we're not allowed to apply a card to itself
						}

						Card::Operation operation = Card::toOperation(
							card->cardData->cardType, 
							sourceCard->getAttack()
						);

						// multiply by negative 1 to flip the diff because we want to hurt the player
						int before = targetCard->getAttack();
						int after = targetCard->simulateOperation(operation);
						int diff = (after - before) * -1;
						if (diff > bestDiff) {
							bestDiff = diff;
							bestSourceCard = sourceCard;
							bestTargetCard = targetCard;
						}
					}
				}

				if (bestDiff >= 0) {
					this->activeGameState->stagedCombineSourceCard = bestSourceCard;
					this->activeGameState->stagedCombineTargetCard = bestTargetCard;
					this->activeGameState->selectedCard = card;
					GameState::updateState(this->activeGameState, GameState::StateType::ControlCombineStaged);
					return;
				}
				break;
			}
			default: 
				break;
		}
	}

	// Unable to find a playable move, so pass
	this->activeGameState->enemyPass = true;
	GameState::updateState(this->activeGameState, GameState::StateType::EndTurn);
}
