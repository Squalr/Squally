#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;
class CardRow;

class StateHandCardStaged : public StateBase
{
public:
	static StateHandCardStaged* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateHandCardStaged();
	~StateHandCardStaged();

	void initializePositions() override;
	void initializeSelectablesAndCallbacks(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageSelectedCombineCard(Card* card, GameState* gameState);
	void immediatelyPlayCard(Card* card, GameState* gameState);
	void onRowChosen(CardRow* cardRow, GameState* gameState);
};
