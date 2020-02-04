#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateDraw : public StateBase
{
public:
	static StateDraw* create();

protected:
	StateDraw();
	virtual ~StateDraw();
	
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
