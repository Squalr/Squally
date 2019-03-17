#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class Card;

class StateCombineStaged : public StateBase
{
public:
	static StateCombineStaged* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateCombineStaged();
	~StateCombineStaged();

	void initializePositions() override;
	void initializeCallbacks(GameState* gameState);
	void selectCard(Card* card, GameState* gameState);
	void stageCombineTarget(Card* card, GameState* gameState);
};
