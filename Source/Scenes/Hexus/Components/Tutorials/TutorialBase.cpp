#include "TutorialBase.h"

TutorialBase::TutorialBase(StateOverride::TutorialMode tutorialMode, GameState::StateType stateToHijack) : super()
{
	this->tutorialMode = tutorialMode;
	this->stateToHijack = stateToHijack;
}

TutorialBase::~TutorialBase()
{
}

void TutorialBase::onEnter()
{
	super::onEnter();

	this->tutorialShown = false;
}

void TutorialBase::onAnyRequestStateChange(GameState* gameState)
{
	super::onAnyRequestStateChange(gameState);

	GameState::StateType previousState = gameState->previousStateType;

	if (!this->tutorialShown && gameState->tutorialMode == this->tutorialMode && gameState->stateType == this->stateToHijack && this->tryHijackState(gameState))
	{
		this->tutorialShown = true;
		this->cachedPreviousState = previousState;

		gameState->stateType = GameState::StateType::Tutorial;
	}
}

void TutorialBase::unHijackState(GameState* gameState)
{
	gameState->stateType = this->cachedPreviousState;
	gameState->updateState(gameState, this->stateToHijack);
}
