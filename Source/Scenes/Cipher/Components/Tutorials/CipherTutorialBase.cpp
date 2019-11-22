#include "CipherTutorialBase.h"

CipherTutorialBase::CipherTutorialBase(CipherState::StateType stateToHijack) : super()
{
	this->stateToHijack = stateToHijack;
}

CipherTutorialBase::~CipherTutorialBase()
{
}

void CipherTutorialBase::onEnter()
{
	super::onEnter();

	this->tutorialShown = false;
	this->isHijacking = false;
}

void CipherTutorialBase::onBeforeAnyRequestStateChange(CipherState* gameState)
{
	super::onBeforeAnyRequestStateChange(gameState);

	this->tryUnHijackState(gameState, false);
}

void CipherTutorialBase::onAnyRequestStateChange(CipherState* gameState)
{
	super::onAnyRequestStateChange(gameState);

	CipherState::StateType previousState = gameState->previousStateType;

	if (!this->tutorialShown && gameState->stateType == this->stateToHijack && this->tryHijackState(gameState))
	{
		this->tutorialShown = true;
		this->isHijacking = true;
		this->cachedPreviousState = previousState;

		gameState->stateType = CipherState::StateType::Tutorial;
	}
}

void CipherTutorialBase::tryUnHijackState(CipherState* gameState, bool updateState)
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
