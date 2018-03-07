#pragma once
#include "cocos2d.h"
#include "Resources.h"
#include "Minigames/Hexium/CardRow.h"
#include "Minigames/Hexium/Deck.h"
#include "MiniGames/Hexium/Config.h"
#include "Utils/StrUtils.h"

using namespace cocos2d;

class GameState
{
public:
	enum StateType {
		CoinFlip,
		FirstSideBanner,
		TurnBanner,
		Draw,
		DrawAnimation,
		Control,
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

	GameState(StateType stateType,
		Turn turn,
		Difficulty difficulty,
		int playerLosses,
		int enemyLosses,
		Card* stagedSacrifice,
		Card* selectedCard,
		std::string bannerMessage,
		std::function<void(Card*)> cardPreviewCallback,
		std::function<void(bool)> updateStateCallback,
		std::function<void()> endTurnCallback,
		std::function<void(GameState*)> requestAiCallback);
	~GameState();

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

	static const std::string onStateUpdateEvent;
};
