#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateOpponentTurnStart : public StateBase
{
public:
	static StateOpponentTurnStart* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateOpponentTurnStart();
	~StateOpponentTurnStart();
};
