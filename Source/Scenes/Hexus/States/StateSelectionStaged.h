#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;
class CardRow;

class StateSelectionStaged : public StateBase
{
public:
	static StateSelectionStaged* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateSelectionStaged();
	~StateSelectionStaged();

	void initializePositions() override;
	void initializeSelectablesAndCallbacks(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageSelectedCombineCard(Card* card, GameState* gameState);
	void immediatelyPlayCard(Card* card, GameState* gameState);
	void onRowChosen(CardRow* cardRow, GameState* gameState);
};
