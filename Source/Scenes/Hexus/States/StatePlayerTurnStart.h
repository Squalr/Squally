#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StatePlayerTurnStart : public StateBase
{
public:
	static StatePlayerTurnStart* create();

protected:
	StatePlayerTurnStart();
	virtual ~StatePlayerTurnStart();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onAfterStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
