#include "StateOverride.h"

StateOverride::StateOverride(
	int playerLosses,
	int enemyLosses,
	bool playersTurn,
	bool playerPassed,
	bool enemyPassed,
	std::vector<CardData*> playerDeck,
	std::vector<CardData*> enemyDeck,
	std::vector<CardData*> playerHand,
	std::vector<CardData*> enemyHand,
	std::vector<CardData*> playerBinaryCards,
	std::vector<CardData*> playerDecimalCards,
	std::vector<CardData*> playerHexCards,
	std::vector<CardData*> enemyBinaryCards,
	std::vector<CardData*> enemyDecimalCards,
	std::vector<CardData*> enemyHexCards)
{
	this->playerLosses = playerLosses;
	this->enemyLosses = enemyLosses;
	this->playersTurn = playersTurn;
	this->playerPassed = playerPassed;
	this->enemyPassed = enemyPassed;
	this->playerDeck = playerDeck;
	this->enemyDeck = enemyDeck;
	this->playerHand = playerHand;
	this->enemyHand = enemyHand;
	this->playerBinaryCards = playerBinaryCards;
	this->playerDecimalCards = playerDecimalCards;
	this->playerHexCards = playerHexCards;
	this->enemyBinaryCards = enemyBinaryCards;
	this->enemyDecimalCards = enemyDecimalCards;
	this->enemyHexCards = enemyHexCards;
}

StateOverride::~StateOverride()
{
}
