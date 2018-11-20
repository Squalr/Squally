#include "StateTutorial.h"

// None of the logic really lives here for tutorials -- see the individual tutorial components

StateTutorial* StateTutorial::create()
{
	StateTutorial* instance = new StateTutorial();

	instance->autorelease();

	return instance;
}

StateTutorial::StateTutorial() : StateBase(GameState::StateType::Tutorial)
{
}

StateTutorial::~StateTutorial()
{
}

void StateTutorial::onAnyStateChange(GameState* gameState)
{
	StateBase::onAnyStateChange(gameState);
}

void StateTutorial::onAnyRequestStateChange(GameState* gameState)
{
	StateBase::onAnyRequestStateChange(gameState);
}

void StateTutorial::onBeforeStateEnter(GameState* gameState)
{
	StateBase::onBeforeStateEnter(gameState);
}

void StateTutorial::onStateEnter(GameState* gameState)
{
	StateBase::onStateEnter(gameState);
}

void StateTutorial::onStateReload(GameState* gameState)
{
	StateBase::onStateReload(gameState);
}

void StateTutorial::onStateExit(GameState* gameState)
{
	StateBase::onStateExit(gameState);
}
