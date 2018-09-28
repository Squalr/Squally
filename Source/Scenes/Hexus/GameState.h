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
		Win,
		Lose,
		GameEnd
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
	void endRound();
	bool playerIsWinning();
	bool enemyIsWinning();
	int getPlayerTotal();
	int getEnemyTotal();
	int getCardCount();
	int getEnemyCardCount();
	int getPlayerCardCount();
	std::vector<CardRow*> getAllRows();
	std::vector<CardRow*> getPlayerRows();
	std::vector<CardRow*> getEnemyRows();
	std::vector<Card*> getAllCards(); 
	std::vector<Card*> getEnemyCards(); 
	std::vector<Card*> getPlayerCards(); 

	StateType stateType;
	StateType previousStateType;
	Turn turn;
	bool playerPass;
	bool enemyPass;
	Difficulty difficulty;
	int playerLosses;
	int enemyLosses;
	int cardReplaceCount;
	int round;
	Card* stagedSacrifice;
	CardRow* stagedSacrificeCardRow;
	CardRow* stagedCombineCardRow;
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
