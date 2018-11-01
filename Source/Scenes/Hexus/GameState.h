#pragma once
#include <chrono>
#include "cocos2d.h"

#include "Engine/Utils/StrUtils.h"
#include "Engine/SmartNode.h"
#include "Events/HexusEvents.h"
#include "Resources.h"
#include "Scenes/Hexus/CardRow.h"
#include "Scenes/Hexus/Config.h"
#include "Scenes/Hexus/Deck.h"
#include "Scenes/Hexus/Opponents/HexusOpponentData.h"

using namespace cocos2d;

class GameState : public SmartNode
{
public:
	enum StateType
	{
		EmptyState,
		GameStart,
		DrawInitialCards,
		Draw,
		CoinFlip,
		RoundStart,
		CardReplace,
		PlayerTurnStart,
		OpponentTurnStart,
		Neutral,
		SelectionStaged,
		CombineStaged,
		Pass,
		LastStand,
		PlayCard,
		AIDecideCard,
		AIDecideCardReplace,
		AIDecidePass,
		AIDecideTarget,
		TurnEnd,
		RoundEnd,
		GameEnd,
	};

	enum Turn
	{
		Player,
		Enemy,
	};

	static GameState * create();
	static void updateState(GameState* gameState, StateType newState);
	void clearInteraction();
	void removeFieldCards();
	bool isRoundTied();
	bool isPlayerWinningRound();
	bool isEnemyWinningRound();
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
	HexusOpponentData::Difficulty difficulty;
	bool isRepeatingSameTurn;
	bool playerPassed;
	bool enemyPassed;
	bool playerLastStanded;
	bool enemyLastStanded;
	int playerLosses;
	int enemyLosses;
	int cardReplaceCount;
	int roundNumber;
	int turnNumber;
	int penaltyCardsPlayed;
	int playableCardsThisTurn;
	int gameDurationInSeconds;
	CardRow* stagedCombineCardRow;
	Card* stagedCombineSourceCard;
	Card* stagedCombineTargetCard;
	Card* selectedCard;
	CardRow* selectedRow;
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

	std::function<void(HexusEvents::HexusGameResultEventArgs)> onGameEndCallback;
	HexusOpponentData* opponentData;

	static const std::string beforeStateUpdateEvent;
	static const std::string onStateUpdateEvent;
private:
	GameState();
	~GameState();

	void initializePositions() override;

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
