#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateAIDecidePass : public StateBase
{
public:
	static StateAIDecidePass* create();

protected:
	StateAIDecidePass();
	virtual ~StateAIDecidePass();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
