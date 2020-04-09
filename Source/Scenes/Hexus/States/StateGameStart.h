#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateGameStart : public StateBase
{
public:
	static StateGameStart* create();

protected:
	StateGameStart();
	virtual ~StateGameStart();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
