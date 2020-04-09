#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;

class StateSourceCardStaged : public StateBase
{
public:
	static StateSourceCardStaged* create();

protected:
	StateSourceCardStaged();
	virtual ~StateSourceCardStaged();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageCombineTarget(Card* card, GameState* gameState);
};
