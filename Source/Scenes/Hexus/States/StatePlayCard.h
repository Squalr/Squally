#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class CardRow;

class StatePlayCard : public StateBase
{
public:
	static StatePlayCard* create();

	static void DoNextTransition(GameState* gameState, bool enterPeekState = false);

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StatePlayCard();
	~StatePlayCard();

	bool tryAbsorb(GameState* gameState, CardRow* cardRow);

	void passFromError(GameState* gameState);
};
