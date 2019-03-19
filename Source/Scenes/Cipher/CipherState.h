#pragma once
#include <chrono>
#include <vector>

#include "Engine/SmartNode.h"

class Card;
class CardRow;
class Deck;

class CipherState : public SmartNode
{
public:
	enum class StateType
	{
		EmptyState,
		LoadInitialState,
		GameStart,
		GameEnd,
		Running,
		Victory,
		Wrong
	};

	static CipherState* create();
	static void updateState(CipherState* gameState, StateType newState);

	StateType stateType;
	StateType previousStateType;
	int gameDurationInSeconds;
	std::function<void(bool)> updateStateCallback;

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

	// Tutorial node pointers
	cocos2d::Node* inputsOutputsPanelPointer;

	static const std::string requestStateUpdateEvent;
	static const std::string beforeStateUpdateEvent;
	static const std::string onStateUpdateEvent;
private:
	CipherState();
	~CipherState();

	void initializePositions() override;
	void clearInteraction();

	std::chrono::time_point<std::chrono::high_resolution_clock> gameStartTime;
	std::chrono::time_point<std::chrono::high_resolution_clock> gameEndTime;
};
