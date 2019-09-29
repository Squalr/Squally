#include "TutorialBase.h"

TutorialBase::TutorialBase(GameState::StateType stateToHijack) : super()
{
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

	if (gameState->stateType == this->stateToHijack && this->tryHijackState(gameState))
	{
		this->tutorialShown = true;
		this->cachedPreviousState = previousState;

		gameState->stateType = GameState::StateType::Tutorial;
	}
	
	if (gameState->stateType == GameState::StateType::GameExit)
	{
		// Cleanup any tutorials that may have not been released (unlikely outside of a debugging context)
		this->unHijackState(gameState);
	}
}

void TutorialBase::unHijackState(GameState* gameState)
{
	gameState->stateType = this->cachedPreviousState;
	gameState->updateState(gameState, this->stateToHijack);
}
