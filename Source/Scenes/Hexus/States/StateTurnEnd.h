#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateTurnEnd : public StateBase
{
public:
	static StateTurnEnd* create();

protected:
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateTurnEnd();
	~StateTurnEnd();
};
