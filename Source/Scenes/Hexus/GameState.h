#pragma once
#include "cocos2d.h"

#include "Engine/Utils/StrUtils.h"
#include "Engine/SmartNode.h"
#include "Resources.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"

using namespace cocos2d;

class GameState : public SmartNode
{
public:
	enum StateType
	{
		EmptyState,
		CoinFlip,
		FirstSideBanner,
		TurnBanner,
		DrawInitialCards,
		Draw,
		ControlReplaceCards,
		ControlNeutral,
		ControlSelectionStaged,
		ControlSacrificeStaged,
		ControlCombineStaged,
		EndTurn,
		Score,
		Finish
	};

	enum Difficulty
	{
		Stupid,
		Easy,
		Medium,
		Hard,
		Expert,
	};

	enum Turn
	{
		Player,
		Enemy,
	};

	static GameState * create();
	static void updateState(GameState* gameState, StateType newState);
	void clearCallbackStates();
	int getPlayerTotal();
	int getEnemyTotal();

	StateType stateType;
	StateType previousStateType;
	Turn turn;
	bool playerPass;
	bool enemyPass;
	Difficulty difficulty;
	int playerLosses;
	int enemyLosses;
	int round;
	Card* stagedSacrifice;
	CardRow* stagedSacrificeCardRow;
	Card* stagedCombineSourceCard;
	Card* stagedCombineTargetCard;
	Card* selectedCard;
	std::string bannerMessage;
	std::set<Card*>* stagedSacrificeTargets;
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

	void initializePositions() override;
};
