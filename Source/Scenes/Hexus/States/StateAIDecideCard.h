#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateAIDecideCard : public StateBase
{
public:
	static StateAIDecideCard* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateAIDecideCard();
	~StateAIDecideCard();

	void decideCardRandom(GameState* gameState);
	void decideCardStrongestFirst(GameState* gameState);
	void decideCardWeakestFirst(GameState* gameState);
};
