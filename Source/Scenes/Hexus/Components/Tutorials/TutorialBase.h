#pragma once

#include "Scenes/Hexus/Components/ComponentBase.h"
#include "Scenes/Hexus/GameState.h"

class ClickableTextNode;

class TutorialBase : public ComponentBase
{
protected:
	TutorialBase(GameState::StateType stateToHijack);
	virtual ~TutorialBase();

	void onEnter() override;
	void onBeforeAnyRequestStateChange(GameState* gameState) override;
	void onAnyRequestStateChange(GameState* gameState) override;
	virtual bool tryHijackState(GameState* gameState) = 0;
	void tryUnHijackState(GameState* gameState, bool updateState = true);
	virtual void unHijackState(GameState* gameState) = 0;

	ClickableTextNode* createNextButton();

	bool tutorialShown = false;
	GameState::StateType cachedPreviousState = GameState::StateType::EmptyState;
	GameState::StateType stateToHijack = GameState::StateType::EmptyState;

private:
	typedef ComponentBase super;

	bool isHijacking = false;
};
