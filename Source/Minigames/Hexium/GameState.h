#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardRow.h"
#include "Minigames/Hexium/Deck.h"
#include "MiniGames/Hexium/Config.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class GameState : Node
{
public:
	enum StateType {
		None,
		CoinFlip,
		FirstSideBanner,
		TurnBanner,
		Draw,
		DrawAnimation,
		Control,
		ControlNeutral,
		ControlSelectionStaged,
		ControlSacrificeStaged,
		EndTurn,
	};

	enum Difficulty {
		None,
		Stupid,
		Easy,
		Medium,
		Hard,
		Expert,
	};

	enum Turn {
		None,
		Player,
		Enemy,
	};

	static GameState * create();
	static void updateState(GameState* gameState, StateType newState);

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

};
