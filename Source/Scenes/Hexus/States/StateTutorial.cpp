#include "StateTutorial.h"

// None of the logic really lives here for tutorials -- see the individual tutorial components

StateTutorial* StateTutorial::create()
{
	StateTutorial* instance = new StateTutorial();

	instance->autorelease();

	return instance;
}

StateTutorial::StateTutorial() : super(GameState::StateType::Tutorial)
{
}

StateTutorial::~StateTutorial()
{
}

void StateTutorial::onAnyStateChange(GameState* gameState)
{
	super::onAnyStateChange(gameState);
}

void StateTutorial::onAnyRequestStateChange(GameState* gameState)
{
	super::onAnyRequestStateChange(gameState);
}

void StateTutorial::onBeforeStateEnter(GameState* gameState)
{
	super::onBeforeStateEnter(gameState);
}

void StateTutorial::onStateEnter(GameState* gameState)
{
	super::onStateEnter(gameState);
}

void StateTutorial::onStateReload(GameState* gameState)
{
	super::onStateReload(gameState);
}

void StateTutorial::onStateExit(GameState* gameState)
{
	super::onStateExit(gameState);
}
