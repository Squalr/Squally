#include "StateBase.h"

#include "cocos/base/CCEventCustom.h"
#include "cocos/base/CCEventListenerCustom.h"

#include "Events/HexusEvents.h"

using namespace cocos2d;

StateBase::StateBase(GameState::StateType stateType)
{
	this->stateType = stateType;
}

StateBase::~StateBase()
{
}

void StateBase::initializeListeners()
{
	super::initializeListeners();

	this->addEventListener(EventListenerCustom::create(HexusEvents::EventRequestStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onRequestStateChangeEvent(eventCustom);
	}));
	this->addEventListener(EventListenerCustom::create(HexusEvents::EventBeforeStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onBeforeStateChangeEvent(eventCustom);
	}));
	this->addEventListener(EventListenerCustom::create(HexusEvents::EventOnStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onStateChangeEvent(eventCustom);
	}));
	this->addEventListener(EventListenerCustom::create(HexusEvents::EventAfterStateUpdate, [=](EventCustom* eventCustom)
	{
		this->onAfterStateChangeEvent(eventCustom);
	}));
}

void StateBase::onRequestStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getData());

	this->onAnyRequestStateChange(gameState);
}

void StateBase::onBeforeStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getData());

	if (gameState->stateType == this->stateType && gameState->previousStateType != this->stateType)
	{
		this->onBeforeStateEnter(gameState);
	}
	else if (gameState->stateType != this->stateType && gameState->previousStateType == this->stateType)
	{
		this->onStateExit(gameState);
	}
}

void StateBase::onStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getData());

	if (gameState->stateType == this->stateType)
	{
		if (gameState->previousStateType == this->stateType)
		{
			this->onStateReload(gameState);
		}
		else
		{
			this->onStateEnter(gameState);
		}
	}

	this->onAnyStateChange(gameState);
}

void StateBase::onAfterStateChangeEvent(EventCustom* eventCustom)
{
	GameState* gameState = (GameState*)(eventCustom->getData());

	if (gameState->stateType == this->stateType)
	{
		if (gameState->previousStateType != this->stateType)
		{
			this->onAfterStateEnter(gameState);
		}
	}

	this->onAfterAnyStateChange(gameState);
}

void StateBase::onAnyStateChange(GameState* gameState)
{
}

void StateBase::onAnyRequestStateChange(GameState* gameState)
{
}

void StateBase::onAfterAnyStateChange(GameState* gameState)
{
}

void StateBase::onBeforeStateEnter(GameState* gameState)
{
}

void StateBase::onStateEnter(GameState* gameState)
{
}

void StateBase::onAfterStateEnter(GameState* gameState)
{
}

void StateBase::onStateReload(GameState* gameState)
{
}

void StateBase::onStateExit(GameState* gameState)
{
}
