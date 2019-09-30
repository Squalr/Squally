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
	this->isHijacking = false;
}

void TutorialBase::onBeforeAnyRequestStateChange(GameState* gameState)
{
	super::onBeforeAnyRequestStateChange(gameState);

	this->tryUnHijackState(gameState, false);
}

void TutorialBase::onAnyRequestStateChange(GameState* gameState)
{
	super::onAnyRequestStateChange(gameState);

	GameState::StateType previousState = gameState->previousStateType;

	if (!this->tutorialShown && gameState->stateType == this->stateToHijack && this->tryHijackState(gameState))
	{
		this->tutorialShown = true;
		this->isHijacking = true;
		this->cachedPreviousState = previousState;

		gameState->stateType = GameState::StateType::Tutorial;
	}
}

void TutorialBase::tryUnHijackState(GameState* gameState, bool updateState)
{
	if (this->isHijacking)
	{
		this->isHijacking = false;

		this->unHijackState(gameState);

		if (updateState)
		{
			gameState->stateType = this->cachedPreviousState;
			gameState->updateState(gameState, this->stateToHijack);
		}
	}
}
