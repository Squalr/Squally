#pragma once

#include "Scenes/Hexus/States/StateBase.h"

class StateTutorial : public StateBase
{
public:
	static StateTutorial* create();

protected:
	void onAnyStateChange(GameState* gameState) override;
	void onAnyRequestStateChange(GameState* gameState) override;
	void onBeforeStateEnter(GameState* gameState) override;
	void onStateEnter(GameState* gameState) override;
	void onStateReload(GameState* gameState) override;
	void onStateExit(GameState* gameState) override;

private:
	StateTutorial();
	~StateTutorial();
};
