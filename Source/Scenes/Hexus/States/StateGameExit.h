#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateGameExit : public StateBase
{
public:
	static StateGameExit* create();

protected:
	StateGameExit();
	virtual ~StateGameExit();

	void onEnter() override;
	void initializePositions() override;
	void initializeListeners() override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	typedef StateBase super;
};
