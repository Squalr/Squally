#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"
#include "Scenes/Hexus/GameState.h"

class TutorialBase : public ComponentBase
{
protected:
	TutorialBase(GameState::StateType stateToHijack);
	~TutorialBase();

	void onEnter() override;
	void onAnyRequestStateChange(GameState* gameState) override;
	virtual bool tryHijackState(GameState* gameState) = 0;
	virtual void unHijackState(GameState* gameState);

	bool tutorialShown;
	GameState::StateType cachedPreviousState;
	GameState::StateType stateToHijack;

private:
	typedef ComponentBase super;
};
