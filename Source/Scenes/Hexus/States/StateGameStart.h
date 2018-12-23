#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateGameStart : public StateBase
{
public:
	static StateGameStart* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateGameStart();
	~StateGameStart();
};
