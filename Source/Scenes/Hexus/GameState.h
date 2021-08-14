#pragma once
#include <chrono>
#include <vector>

#include "Scenes/Hexus/Opponents/HexusOpponentData.h"
#include "Scenes/Hexus/StateOverride.h"
#include "Scenes/Platformer/Inventory/Items/PlatformerItems.h"
#include "Engine/SmartNode.h"

class Card;
class CardRow;
class CardPreviewComponent;
class ClickableNode;
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
		PeekCards,
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
		GameExit,
	};

	enum class Turn
	{
		Player,
		Enemy,
	};

	static GameState* create();
	static void updateState(GameState* gameState, StateType newState);
	void clearInteraction();
	void sendFieldCardsToGraveyard(bool playerWon, bool enemyWon);
	bool isRoundTied();
	bool isPlayerWinningRound();
	bool isEnemyWinningRound();
	int getPlayerLosses();
	int getEnemyLosses();
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
	CardRow* getRowForCard(Card* card);
	std::vector<CardRow*> getAllRows();
	std::vector<CardRow*> getPlayerRows();
	std::vector<CardRow*> getEnemyRows();
	std::vector<Card*> getAllCards(); 
	std::vector<Card*> getEnemyCards(); 
	std::vector<Card*> getPlayerCards();
	std::vector<Card*> getAbsorbCards();

	StateType stateType = StateType::EmptyState;
	StateType previousStateType= StateType::EmptyState;
	Turn turn = Turn::Player;
	HexusOpponentData::Strategy difficulty = HexusOpponentData::Strategy::Random;
	bool isRepeatingSameTurn = false;
	bool playerPassed = false;
	bool enemyPassed = false;
	int playerLosses = 0;
	int enemyLosses = 0;
	int cardReplaceCount = 0;
	int roundNumber = 0;
	int turnNumber = 0;
	int playerCardsDrawnNextRound = 0;
	int enemyCardsDrawnNextRound = 0;
	int playableCardsThisTurn = 0;
	int gameDurationInSeconds = 0;
	bool showChallengeBanner = 0;
	Card* selectedSourceCard = nullptr;
	Card* selectedDestinationCard = nullptr;
	Card* selectedHandCard = nullptr;
	CardRow* selectedRow = nullptr;
	std::string bannerMessage;
	std::function<void(Card*)> cardPreviewComponentCallback = nullptr;
	std::function<void(bool)> updateStateCallback = nullptr;
	std::function<void()> endTurnCallback = nullptr;
	std::function<void(GameState*)> requestAiCallback = nullptr;

	std::tuple<CardRow*, int> cachedBestRowPlay;
	std::tuple<Card*, Card*, int> cachedBestSourceTargetPlay;
	std::tuple<Card*, int> cachedBestTargetPlay;

	Deck* playerDeck = nullptr;
	CardRow* playerHand = nullptr;
	Deck* playerGraveyard = nullptr;
	CardRow* playerBinaryCards = nullptr;
	CardRow* playerDecimalCards = nullptr;
	CardRow* playerHexCards = nullptr;

	Deck* enemyDeck = nullptr;
	CardRow* enemyHand = nullptr;
	Deck* enemyGraveyard = nullptr;
	CardRow* enemyBinaryCards = nullptr;
	CardRow* enemyDecimalCards = nullptr;
	CardRow* enemyHexCards = nullptr;

	ClickableNode* boardSelection = nullptr;

	HexusOpponentData* opponentData = nullptr;

	// Tutorial node pointers
	cocos2d::Node* lossesDisplayPointer = nullptr;
	cocos2d::Node* playerBinaryRowTotalPointer = nullptr;
	cocos2d::Node* playerDecimalRowTotalPointer = nullptr;
	cocos2d::Node* playerHexRowTotalPointer = nullptr;
	cocos2d::Node* enemyBinaryRowTotalPointer = nullptr;
	cocos2d::Node* enemyDecimalRowTotalPointer = nullptr;
	cocos2d::Node* enemyHexRowTotalPointer = nullptr;
	cocos2d::Node* scoreTotalPointer = nullptr;
	cocos2d::Node* deckCardCountDisplayPointer = nullptr;
	cocos2d::Node* handCardCountDisplayPointer = nullptr;
	cocos2d::Node* remainingCardDisplayPointer = nullptr;
	cocos2d::Node* drawCountDisplayPointer = nullptr;
	cocos2d::Node* passButtonPointer = nullptr;
	cocos2d::Node* lastStandButtonPointer = nullptr;
	cocos2d::Node* claimVictoryButtonPointer = nullptr;
	CardPreviewComponent* cardPreviewPointer = nullptr;

protected:
	GameState();
	virtual ~GameState();

	void initializePositions() override;
	void onDeveloperModeEnable(int debugLevel) override;
	void onDeveloperModeDisable() override;

private:
	typedef SmartNode super;

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
