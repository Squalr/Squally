#include "GameState.h"

#include "cocos/base/CCDirector.h"
#include "cocos/base/CCEventDispatcher.h"

#include "Engine/Input/ClickableNode.h"
#include "Engine/Utils/StrUtils.h"
#include "Events/HexusEvents.h"
#include "Scenes/Hexus/Card.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/HexusConfig.h"

#include "Resources/HexusResources.h"
#include "Resources/EntityResources.h"
#include "Resources/UIResources.h"

using namespace cocos2d;

GameState* GameState::create()
{
	GameState* instance = new GameState();

	instance->autorelease();

	return instance;
}

GameState::GameState()
	: stateType(StateType::EmptyState),
	turn(Turn::Player),
	difficulty(HexusOpponentData::Strategy::Random),
	playerLosses(0),
	enemyLosses(0),
	cardReplaceCount(0),
	isRepeatingSameTurn(false),
	playerPassed(false),
	enemyPassed(false),
	turnNumber(0),
	playableCardsThisTurn(0),
	playerCardsDrawnNextRound(0),
	enemyCardsDrawnNextRound(0),
	roundNumber(0),
	opponentData(nullptr),
	gameDurationInSeconds(0),
	showChallengeBanner(false),
	selectedHandCard(nullptr),
	selectedRow(nullptr),
	cardPreviewComponentCallback(nullptr),
	updateStateCallback(nullptr),
	endTurnCallback(nullptr),
	requestAiCallback(nullptr),
	selectedSourceCard(nullptr),
	selectedDestinationCard(nullptr)
{
	this->playerDeck = Deck::create();
	this->playerHand = CardRow::create(true);
	this->playerGraveyard = Deck::create();
	this->playerBinaryCards = CardRow::create(true);
	this->playerDecimalCards = CardRow::create(true);
	this->playerHexCards = CardRow::create(true);

	this->enemyDeck = Deck::create(false);
	this->enemyHand = CardRow::create(false);
	this->enemyGraveyard = Deck::create(false);
	this->enemyBinaryCards = CardRow::create(false);
	this->enemyDecimalCards = CardRow::create(false);
	this->enemyHexCards = CardRow::create(false);

	this->lossesDisplayPointer = nullptr;
	this->playerBinaryRowTotalPointer = nullptr;
	this->playerDecimalRowTotalPointer = nullptr;
	this->playerHexRowTotalPointer = nullptr;
	this->enemyBinaryRowTotalPointer = nullptr;
	this->enemyDecimalRowTotalPointer = nullptr;
	this->enemyHexRowTotalPointer = nullptr;
	this->scoreTotalPointer = nullptr;
	this->deckCardCountDisplayPointer = nullptr;
	this->handCardCountDisplayPointer = nullptr;
	this->remainingCardDisplayPointer = nullptr;
	this->drawCountDisplayPointer = nullptr;
	this->passButtonPointer = nullptr;
	this->lastStandButtonPointer = nullptr;
	this->claimVictoryButtonPointer = nullptr;
	this->cardPreviewPointer = nullptr;

	this->playerHand->setRowWidth(HexusConfig::handWidth, 0.0f);
	this->enemyHand->setRowWidth(HexusConfig::enemyHandWidth, 0.0f);

	this->playerHand->enableClearOperationsOnInsert();
	this->enemyHand->enableClearOperationsOnInsert();
	this->playerGraveyard->enableClearOperationsOnInsert();
	this->enemyGraveyard->enableClearOperationsOnInsert();
	this->playerDeck->enableClearOperationsOnInsert();
	this->enemyDeck->enableClearOperationsOnInsert();

	this->addChild(this->enemyGraveyard);
	this->addChild(this->enemyDeck);
	this->addChild(this->enemyHexCards);
	this->addChild(this->enemyDecimalCards);
	this->addChild(this->enemyBinaryCards);
	this->addChild(this->enemyHand);

	this->addChild(this->playerGraveyard);
	this->addChild(this->playerDeck);
	this->addChild(this->playerHexCards);
	this->addChild(this->playerDecimalCards);
	this->addChild(this->playerBinaryCards);
	this->addChild(this->playerHand);
}

GameState::~GameState()
{
}

void GameState::initializePositions()
{
	super::initializePositions();

	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyGraveyard->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::graveyardOffsetX, visibleSize.height / 2.0f + HexusConfig::graveyardOffsetY);
	this->playerGraveyard->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::graveyardOffsetX, visibleSize.height / 2.0f - HexusConfig::graveyardOffsetY);

	this->playerDeck->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::deckOffsetX, visibleSize.height / 2.0f - HexusConfig::deckOffsetY);
	this->enemyDeck->setPosition(visibleSize.width / 2.0f + HexusConfig::rightColumnCenter + HexusConfig::deckOffsetX, visibleSize.height / 2.0f + HexusConfig::deckOffsetY);

	this->playerHand->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f - HexusConfig::handOffsetY);
	this->playerBinaryCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY - HexusConfig::binaryRowOffsetY);
	this->playerDecimalCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY - HexusConfig::decimalRowOffsetY);
	this->playerHexCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY - HexusConfig::hexRowOffsetY);

	this->enemyHand->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::handOffsetY + 256.0f);
	this->enemyBinaryCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY + HexusConfig::binaryRowOffsetY);
	this->enemyDecimalCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY + HexusConfig::decimalRowOffsetY);
	this->enemyHexCards->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::boardCenterOffsetY + HexusConfig::hexRowOffsetY);
}

void GameState::onDeveloperModeEnable(int debugLevel)
{
	super::onDeveloperModeEnable(debugLevel);

	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyHand->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::handOffsetY);
	*/
}

void GameState::onDeveloperModeDisable()
{
	super::onDeveloperModeDisable();

	/*
	Size visibleSize = Director::getInstance()->getVisibleSize();

	this->enemyHand->setPosition(visibleSize.width / 2.0f + HexusConfig::centerColumnCenter, visibleSize.height / 2.0f + HexusConfig::handOffsetY + 256.0f);
	*/
}

void GameState::updateState(GameState* gameState, StateType newState)
{
	if (gameState == nullptr)
	{
		return;
	}

	gameState->previousStateType = gameState->stateType;
	gameState->stateType = newState;
	gameState->clearInteraction();

	// This seems to fix a bug where the game camera is zoomed out when the hexus match starts, causing these to have invalid positions:	
	gameState->enemyHand->setCardScale(Card::cardScale, 0.0f);
	gameState->enemyDeck->setCardScale(Card::cardScale, 0.25f);
	gameState->playerDeck->setCardScale(Card::cardScale, 0.25f);
	gameState->enemyHand->setCardPositions(0.01f);
	gameState->enemyDeck->setCardPositions(0.01f);
	gameState->playerDeck->setCardPositions(0.01f);

	switch (newState)
	{
		case StateType::GameStart:
		{
			gameState->gameStartTime = std::chrono::high_resolution_clock::now();
			break;
		}
		case StateType::GameEnd:
		{
			gameState->gameEndTime = std::chrono::high_resolution_clock::now();
			std::chrono::duration<double> elapsed = gameState->gameEndTime - gameState->gameStartTime;
			gameState->gameDurationInSeconds = (int)(elapsed.count());
			break;
		}
		default:
		{
			break;
		}
	}

	HexusEvents::TriggerBeforeRequestStateUpdate(gameState);
	HexusEvents::TriggerRequestStateUpdate(gameState);
	HexusEvents::TriggerBeforeStateUpdate(gameState);
	HexusEvents::TriggerOnStateUpdate(gameState);
	HexusEvents::TriggerAfterStateUpdate(gameState);
}

void GameState::clearInteraction()
{
	this->playerHand->setMouseClickCallback(nullptr);
	this->playerHand->setMouseOverCallback(nullptr);
	this->enemyHand->setMouseClickCallback(nullptr);
	this->enemyHand->setMouseOverCallback(nullptr);

	this->playerDeck->disableDeckSelection();
	this->enemyDeck->disableDeckSelection();
	this->playerGraveyard->disableDeckSelection();
	this->enemyGraveyard->disableDeckSelection();
	
	this->playerDeck->disableInteraction();
	this->enemyDeck->disableInteraction();
	this->playerGraveyard->disableInteraction();
	this->enemyGraveyard->disableInteraction();

	this->enemyHand->disableRowSelection();
	this->enemyHand->disableRowCardSelection();
	this->enemyHand->disableRowCardInteraction();
	this->playerHand->disableRowSelection();
	this->playerHand->disableRowCardSelection();
	this->playerHand->disableRowCardInteraction();

	this->boardSelection->disableInteraction(0);

	std::vector<CardRow*> rows = this->getAllRows();

	for (auto row : rows)
	{
		row->disableRowSelection();
		row->disableRowCardSelection();
		row->disableRowCardInteraction();
	}
}

void GameState::sendFieldCardsToGraveyard(bool playerWon, bool enemyWon)
{
	std::vector<CardRow*> playerRows = this->getPlayerRows();
	std::vector<Card*> playerRemovedCards = std::vector<Card*>();
	std::vector<CardRow*> enemyRows = this->getEnemyRows();
	std::vector<Card*> enemyRemovedCards = std::vector<Card*>();
	bool isGameOver = this->playerLosses >= 2 || this->enemyLosses >= 2;

	for (auto row : playerRows)
	{
		row->removeCardsWhere([&](Card* card)
		{
			// Special effect for binary 0 card (unless the game is over)
			if (!isGameOver && card->cardData->getCardKey() == CardKeys::Binary0)
			{
				return false;
			}

			playerRemovedCards.push_back(card);
			return true;
		});
	}

	for (auto row : enemyRows)
	{
		row->removeCardsWhere([&](Card* card)
		{
			// Special effect for binary 0 card (unless the game is over)
			if (!isGameOver && card->cardData->getCardKey() == CardKeys::Binary0)
			{
				return false;
			}

			enemyRemovedCards.push_back(card);
			return true;
		});
	}

	for (auto card : playerRemovedCards)
	{
		// Special effect for Dec1 cards
		if (!isGameOver && card->cardData->getCardKey() == CardKeys::Decimal1)
		{
			if (card->getIsPlayerOwnedCard())
			{
				this->playerHand->insertCard(card, HexusConfig::insertDelay);
			}
			else
			{
				this->enemyHand->insertCard(card, HexusConfig::insertDelay);
			}
		}
		else
		{
			if (card->getIsPlayerOwnedCard())
			{
				this->playerGraveyard->insertCardTop(card, true, HexusConfig::insertDelay);
			}
			else
			{
				this->enemyGraveyard->insertCardTop(card, true, HexusConfig::insertDelay);
			}
		}
	}

	for (auto card : enemyRemovedCards)
	{
		// Special effect for Dec1 cards
		if (!isGameOver && card->cardData->getCardKey() == CardKeys::Decimal1)
		{
			if (card->getIsPlayerOwnedCard())
			{
				this->playerHand->insertCard(card, HexusConfig::insertDelay);
			}
			else
			{
				this->enemyHand->insertCard(card, HexusConfig::insertDelay);
			}
		}
		else
		{
			if (card->getIsPlayerOwnedCard())
			{
				this->playerGraveyard->insertCardTop(card, true, HexusConfig::insertDelay);
			}
			else
			{
				this->enemyGraveyard->insertCardTop(card, true, HexusConfig::insertDelay);
			}
		}
	}
}

CardRow* GameState::getRowForCard(Card* card)
{
	for (auto row : this->getAllRows())
	{
		for (auto rowCard : row->rowCards)
		{
			if (rowCard == card)
			{
				return row;
			}
		}
	}

	return nullptr;
}

std::vector<Card*> GameState::getAllCards() 
{
	std::vector<Card*> cards;

	for (auto row : this->getAllRows())
	{
		for (auto rowCard : row->rowCards)
		{
			cards.push_back(rowCard);
		}
	}

	return cards;
}

std::vector<Card*> GameState::getEnemyCards() 
{
	std::vector<Card*> cards;

	for (auto row : this->getEnemyRows())
	{
		for (auto rowCard : row->rowCards)
		{
			cards.push_back(rowCard);
		}
	}

	return cards;
}

std::vector<Card*> GameState::getPlayerCards() 
{
	std::vector<CardRow*> rows = this->getPlayerRows();
	std::vector<Card*> cards;

	for (auto row : this->getPlayerRows())
	{
		for (auto rowCard : row->rowCards)
		{
			cards.push_back(rowCard);
		}
	}

	return cards;
}

std::vector<Card*> GameState::getAbsorbCards()
{
	std::vector<Card*> absorbCards = std::vector<Card*>();

	for (auto card : this->getAllCards())
	{
		if (card->cardData->getCardType() == CardData::CardType::Special_ABSORB)
		{
			absorbCards.push_back(card);
		}
	}

	return absorbCards;
}

std::vector<CardRow*> GameState::getAllRows() 
{
	std::vector<CardRow*> rows = std::vector<CardRow*>();
	std::vector<CardRow*> enemyRows = this->getEnemyRows();
	std::vector<CardRow*> playerRows = this->getPlayerRows();

	rows.insert(rows.end(), enemyRows.begin(), enemyRows.end());
	rows.insert(rows.end(), playerRows.begin(), playerRows.end());

	return rows;
}

std::vector<CardRow*> GameState::getEnemyRows() 
{
	std::vector<CardRow*> cardRows;

	cardRows.push_back(this->enemyDecimalCards);
	cardRows.push_back(this->enemyHexCards);
	cardRows.push_back(this->enemyBinaryCards);

	return cardRows;
}

std::vector<CardRow*> GameState::getPlayerRows() 
{
	std::vector<CardRow*> cardRows = std::vector<CardRow*>();

	cardRows.push_back(this->playerDecimalCards);
	cardRows.push_back(this->playerHexCards);
	cardRows.push_back(this->playerBinaryCards);

	return cardRows;
}

int GameState::getPlayerLosses()
{
	return this->playerLosses;
}

int GameState::getEnemyLosses()
{
	return this->enemyLosses;
}

int GameState::getPlayerTotal()
{
	int total = 0;

	total += this->playerBinaryCards->getRowAttack();
	total += this->playerDecimalCards->getRowAttack();
	total += this->playerHexCards->getRowAttack();

	return total;
}

int GameState::getEnemyTotal()
{
	int total = 0;

	total += this->enemyBinaryCards->getRowAttack();
	total += this->enemyDecimalCards->getRowAttack();
	total += this->enemyHexCards->getRowAttack();

	return total;
}

int GameState::getCardCount()
{
	return this->getPlayerCardCount() + this->getEnemyCardCount();
}

int GameState::getPlayerCardCount()
{
	int total = 0;

	total += this->playerBinaryCards->getCardCount();
	total += this->playerDecimalCards->getCardCount();
	total += this->playerHexCards->getCardCount();

	return total;
}

int GameState::getEnemyCardCount()
{
	int total = 0;

	total += this->enemyBinaryCards->getCardCount();
	total += this->enemyDecimalCards->getCardCount();
	total += this->enemyHexCards->getCardCount();

	return total;
}

bool GameState::isRoundTied()
{
	return this->getEnemyTotal() == this->getPlayerTotal();
}

bool GameState::isEnemyWinningRound()
{
	return this->getEnemyTotal() > this->getPlayerTotal();
}

bool GameState::isPlayerWinningRound()
{
	return this->getPlayerTotal() > this->getEnemyTotal();
}

bool GameState::isPlayerLastStandCondition()
{
	return (this->isPlayerWinningRound() && !this->enemyPassed);
}

bool GameState::isPlayerClaimVictoryCondition()
{
	return (this->isPlayerWinningRound() && this->enemyPassed);
}

bool GameState::isPlayerPassCondition()
{
	return (!this->isPlayerLastStandCondition() && !this->isPlayerClaimVictoryCondition());
}

bool GameState::isEnemyLastStandCondition()
{
	return (this->isEnemyWinningRound() && !this->playerPassed);
}

bool GameState::isEnemyClaimVictoryCondition()
{
	return (this->isEnemyWinningRound() && this->playerPassed);
}

bool GameState::isEnemyPassCondition()
{
	return (!this->isEnemyLastStandCondition() && !this->isEnemyClaimVictoryCondition());
}
