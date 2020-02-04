#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateOverride;

class StateLoadInitialState : public StateBase
{
public:
	static StateLoadInitialState* create();

protected:
	StateLoadInitialState();
	virtual ~StateLoadInitialState();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;

	void loadStateOverrides(GameState* gameState, StateOverride* stateOverride);
};
