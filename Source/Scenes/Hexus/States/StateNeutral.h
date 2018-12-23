#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;

class StateNeutral : public StateBase
{
public:
	static StateNeutral* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateNeutral();
	~StateNeutral();

	void initializeCallbacks(GameState* gameState);
	void selectCard(Card* card);

	GameState* activeGameState;
};
