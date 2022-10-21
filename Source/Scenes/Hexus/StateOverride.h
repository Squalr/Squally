#pragma once

#include "Engine/SmartNode.h"

class CardData;
class TutorialBase;

// A class for loading an initial state into Hexus -- used in puzzles and tutorials
class StateOverride : public SmartNode
{
public:
	static StateOverride* create(
		int playerLosses,
		int enemyLosses,
		bool playersTurn,
		bool playerPassed,
		bool enemyPassed,
		std::vector<CardData*> playerDeck,
		std::vector<CardData*> enemyDeck,
		std::vector<CardData*> playerGraveyard,
		std::vector<CardData*> enemyGraveyard,
		std::vector<CardData*> playerHand,
		std::vector<CardData*> enemyHand,
		std::vector<CardData*> playerBinaryCards,
		std::vector<CardData*> playerDecimalCards,
		std::vector<CardData*> playerHexCards,
		std::vector<CardData*> enemyBinaryCards,
		std::vector<CardData*> enemyDecimalCards,
		std::vector<CardData*> enemyHexCards,
		bool showChallengeBanner = true
	);

	int playerLosses = 0;
	int enemyLosses = 0;
	bool playersTurn = 0;
	bool playerPassed = 0;
	bool enemyPassed = 0;
	std::vector<CardData*> playerDeck;
	std::vector<CardData*> enemyDeck;
	std::vector<CardData*> playerGraveyard;
	std::vector<CardData*> enemyGraveyard;
	std::vector<CardData*> playerHand;
	std::vector<CardData*> enemyHand;
	std::vector<CardData*> playerBinaryCards;
	std::vector<CardData*> playerDecimalCards;
	std::vector<CardData*> playerHexCards;
	std::vector<CardData*> enemyBinaryCards;
	std::vector<CardData*> enemyDecimalCards;
	std::vector<CardData*> enemyHexCards;
	bool showChallengeBanner = false;

protected:
	StateOverride();
	StateOverride(
		int playerLosses,
		int enemyLosses,
		bool playersTurn,
		bool playerPassed,
		bool enemyPassed,
		std::vector<CardData*> playerDeck,
		std::vector<CardData*> enemyDeck,
		std::vector<CardData*> playerGraveyard,
		std::vector<CardData*> enemyGraveyard,
		std::vector<CardData*> playerHand,
		std::vector<CardData*> enemyHand,
		std::vector<CardData*> playerBinaryCards,
		std::vector<CardData*> playerDecimalCards,
		std::vector<CardData*> playerHexCards,
		std::vector<CardData*> enemyBinaryCards,
		std::vector<CardData*> enemyDecimalCards,
		std::vector<CardData*> enemyHexCards,
		bool showChallengeBanner
	);
	virtual ~StateOverride();

private:
	typedef SmartNode super;
};
