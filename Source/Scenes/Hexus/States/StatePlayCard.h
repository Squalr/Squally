#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StatePlayCard : public StateBase
{
public:
	static StatePlayCard* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StatePlayCard();
	~StatePlayCard();

	void passFromError(GameState* gameState);
};
