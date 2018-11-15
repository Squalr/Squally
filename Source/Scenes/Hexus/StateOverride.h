#pragma once
#include "cocos2d.h"

#include "Engine/SmartNode.h"
#include "Resources.h"
#include "Scenes/Hexus/CardData/CardData.h"
#include "Scenes/Hexus/CardData/CardList.h"
#include "Scenes/Hexus/CardData/CardKeys.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

// A class for loading an initial state into Hexus -- used in puzzles and tutorials
class StateOverride : public SmartNode
{
public:
	int playerLosses;
	int enemyLosses;
	bool playersTurn;
	bool playerPassed;
	bool enemyPassed;
	std::vector<CardData*> playerDeck;
	std::vector<CardData*> enemyDeck;
	std::vector<CardData*> playerHand;
	std::vector<CardData*> enemyHand;
	std::vector<CardData*> playerBinaryCards;
	std::vector<CardData*> playerDecimalCards;
	std::vector<CardData*> playerHexCards;
	std::vector<CardData*> enemyBinaryCards;
	std::vector<CardData*> enemyDecimalCards;
	std::vector<CardData*> enemyHexCards;

protected:
	StateOverride(
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
		std::vector<CardData*> enemyHexCards
	);
	~StateOverride();

};
