#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardRow.h"
#include "Minigames/Hexium/Deck.h"
#include "MiniGames/Hexium/Config.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class GameState : public Node
{
public:
	static GameState * create();

	void gameStart(Deck* startPlayerDeck, Deck* startEnemyDeck);
	void randomizeTurn();
	void drawCard();
	void giveControl();
	void endTurn();
	void setCardPreviewCallback(std::function<void(Card*)> callback);
	void setUpdateStateCallback(std::function<void(bool)> callback);
	void setRequestAiCallback(std::function<void(GameState*)> callback);

	enum Difficulty {
		Stupid,
		Easy,
		Medium,
		Hard,
		Expert,
	};

	enum Turn {
		Player,
		Enemy,
	};

	// Game state
	Turn turn;
	Difficulty difficulty;
	int playerLosses;
	int enemyLosses;

	Deck* playerDeck;
	CardRow* playerHand;
	Deck* playerGraveyard;
	CardRow* playerBinaryCards;
	CardRow* playerDecimalCards;
	CardRow* playerHexCards;

	Deck* enemyDeck;
	CardRow* enemyHand;
	Deck* enemyGraveyard;
	CardRow* enemyBinaryCards;
	CardRow* enemyDecimalCards;
	CardRow* enemyHexCards;

private:
	GameState();
	~GameState();
	void onEnter() override;
	void onCardMouseOver(Card* card);
	void onHandCardClick(Card* card);
	void onRowCardClick(Card* card);

	void enableUserInteraction();
	void disableUserInteraction();

	void initializePositions();
	void initializeListeners();

	std::function<void(Card*)> cardPreviewCallback;
	std::function<void(bool)> updateStateCallback;
	std::function<void(GameState*)> requestAiCallback;
};

