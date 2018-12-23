#pragma once
#include <chrono>
#include <vector>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Engine/SmartNode.h"

class Card;
class CardRow;
class Deck;
class HexusOpponentData;

class GameState : public SmartNode
{
public:
	enum class StateType
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

	enum class Turn
	{
		Player,
		Enemy,
	};

	static GameState* create();
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

	HexusOpponentData* opponentData;

	// Tutorial node pointers
	cocos2d::Node* lossesDisplayPointer;
	cocos2d::Node* playerBinaryRowTotalPointer;
	cocos2d::Node* playerDecimalRowTotalPointer;
	cocos2d::Node* playerHexRowTotalPointer;
	cocos2d::Node* enemyBinaryRowTotalPointer;
	cocos2d::Node* enemyDecimalRowTotalPointer;
	cocos2d::Node* enemyHexRowTotalPointer;
	cocos2d::Node* scoreTotalPointer;
	cocos2d::Node* deckCardCountDisplayPointer;
	cocos2d::Node* handCardCountDisplayPointer;
	cocos2d::Node* remainingCardDisplayPointer;
	cocos2d::Node* drawCountDisplayPointer;
	cocos2d::Node* passButtonPointer;
	cocos2d::Node* lastStandButtonPointer;
	cocos2d::Node* claimVictoryButtonPointer;

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
