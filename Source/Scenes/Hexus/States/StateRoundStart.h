#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateRoundStart : public StateBase
{
public:
	static StateRoundStart* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
	StateRoundStart();
	~StateRoundStart();
};
