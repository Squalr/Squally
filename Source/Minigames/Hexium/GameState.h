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
	enum StateType {
		CoinFlip,
		FirstSideBanner,
		TurnBanner,
		DrawInitialCards,
		Draw,
		Control,
		ControlNeutral,
		ControlSelectionStaged,
		ControlSacrificeStaged,
		EndTurn,
	};

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

	static GameState * create();
	static void updateState(GameState* gameState, StateType newState);
	void clearCallbackStates();
	int getPlayerTotal();
	int getEnemyTotal();

	StateType stateType;
	Turn turn;
	Difficulty difficulty;
	int playerLosses;
	int enemyLosses;
	Card* stagedSacrifice;
	Card* selectedCard;
	std::string bannerMessage;
	std::function<void(Card*)> cardPreviewCallback;
	std::function<void(bool)> updateStateCallback;
	std::function<void()> endTurnCallback;
	std::function<void(GameState*)> requestAiCallback;

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

	static const std::string onStateUpdateEvent;
private:
	GameState();
	~GameState();

	void onEnter() override;
	void initializePositions();
	void initializeListeners();
};
