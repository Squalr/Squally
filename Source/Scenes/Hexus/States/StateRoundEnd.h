#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateRoundEnd : public StateBase
{
public:
	static StateRoundEnd* create();

protected:
	StateRoundEnd();
	virtual ~StateRoundEnd();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
