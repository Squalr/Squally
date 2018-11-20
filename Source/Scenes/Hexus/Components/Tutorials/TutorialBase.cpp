#include "TutorialBase.h"

TutorialBase::TutorialBase() : ComponentBase()
{
}

TutorialBase::~TutorialBase()
{
}

void TutorialBase::onEnter()
{
	ComponentBase::onEnter();

	this->tutorialShown = false;
}

void TutorialBase::onAnyRequestStateChange(GameState* gameState)
{
	ComponentBase::onAnyRequestStateChange(gameState);

	if (!this->tutorialShown && this->tryHijackState(gameState))
	{
		this->tutorialShown = true;

		gameState->stateType = GameState::StateType::Tutorial;
	}
}
