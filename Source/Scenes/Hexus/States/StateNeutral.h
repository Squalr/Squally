#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;

class StateNeutral : public StateBase
{
public:
	static StateNeutral* create();

protected:
	StateNeutral();
	virtual ~StateNeutral();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void initializeCallbacks(GameState* gameState);
	void selectCard(Card* card);

	GameState* activeGameState;
};
