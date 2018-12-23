#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"
#include "Scenes/Hexus/GameState.h"

class TutorialBase : public ComponentBase
{
protected:
	TutorialBase(StateOverride::TutorialMode tutorialMode, GameState::StateType stateToHijack);
	~TutorialBase();

	void onEnter() override;
	void onAnyRequestStateChange(GameState* gameState) override;
	virtual bool tryHijackState(GameState* gameState) = 0;
	void unHijackState(GameState* gameState);

	bool tutorialShown;
	GameState::StateType cachedPreviousState;
	StateOverride::TutorialMode tutorialMode;
	GameState::StateType stateToHijack;
};
