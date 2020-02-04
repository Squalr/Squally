#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateAIDecideTarget : public StateBase
{
public:
	static StateAIDecideTarget* create();

protected:
	StateAIDecideTarget();
	virtual ~StateAIDecideTarget();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
