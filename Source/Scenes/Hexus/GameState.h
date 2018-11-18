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
		LoadInitialState,
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
		PlayCard,
		AIDecideCard,
		AIDecideCardReplace,
		AIDecidePass,
		AIDecideTarget,
		TurnEnd,
		RoundEnd,
		GameEnd,
		Tutorial,
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
	bool isPlayerLastStandCondition();
	bool isPlayerClaimVictoryCondition();
	bool isPlayerPassCondition();
	bool isEnemyLastStandCondition();
	bool isEnemyClaimVictoryCondition();
	bool isEnemyPassCondition();
	std::vector<CardRow*> getAllRows();
	std::vector<CardRow*> getPlayerRows();
	std::vector<CardRow*> getEnemyRows();
	std::vector<Card*> getAllCards(); 
	std::vector<Card*> getEnemyCards(); 
	std::vector<Card*> getPlayerCards();

	StateType stateType;
	StateType previousStateType;
	Turn turn;
	HexusOpponentData::Strategy difficulty;
	StateOverride::TutorialMode tutorialMode;
	bool isRepeatingSameTurn;
	bool playerPassed;
	bool enemyPassed;
	int playerLosses;
	int enemyLosses;
	int cardReplaceCount;
	int roundNumber;
	int turnNumber;
	int playerCardsDrawnNextRound;
	int enemyCardsDrawnNextRound;
	int playableCardsThisTurn;
	int gameDurationInSeconds;
	Card* selectedSourceCard;
	Card* selectedDestinationCard;
	Card* selectedHandCard;
	CardRow* selectedRow;
	std::string bannerMessage;
	std::function<void(Card*)> cardPreviewCallback;
	std::function<void(bool)> updateStateCallback;
	std::function<void()> endTurnCallback;
	std::function<void(GameState*)> requestAiCallback;

	std::tuple<CardRow*, int> cachedBestRowPlay;
	std::tuple<Card*, Card*, int> cachedBestSourceTargetPlay;
	std::tuple<Card*, int> cachedBestTargetPlay;

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

	static const std::string requestStateUpdateEvent;
	static const std::string beforeStateUpdateEvent;
	static const std::string onStateUpdateEvent;
private:
	GameState();
	~GameState();

	void initializePositions() override;

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
